#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
//
// Created by redneath on 16/07/23.
//

#include <fstream>
#include "nlohmann/json.hpp"
#include "JsonGameLoader.h"
#include "exceptions/SaveNotFound.h"
#include "exceptions/EquipmentNotFound.h"
#include "exceptions/ItemNotFound.h"
#include "exceptions/SkillNotFound.h"

using JsonDictionary = nlohmann::json;
using namespace std;

Game *JsonGameLoader::LoadDataAndAssets(GameSettings settings) {
    Player *player = LoadPlayer(settings.SaveName);
    HeavyResourcesCache<Map> *mapCache = new HeavyResourcesCache<Map>(settings.MapCacheSize);

    // Putting the current map within the cache
    // If we tried to be smart, we could evaluate what maps are the most likely to appear next in memory and already
    // load them in the cache.
    mapCache->Put(to_string(player->GetMap()->GetId()), player->GetMap());

    Game *game = new Game(player, mapCache);

    // Now that we have the game instance, we can load the global values. Being referenced in the Game object itself
    // will automatically turn them into "singletons".
    JsonDictionary globalVariables = GetData(SAVES_DIR + settings.SaveName + SAVE_GLOBAL_VARIABLES);
    ParseAndAffectGlobalVariables(game, globalVariables);

    return game;
}

#pragma region GetData

JsonDictionary JsonGameLoader::GetSaveMetadata(const string &saveName) {
    return GetData(SAVES_DIR + saveName + METADATA_FILE);
}

JsonDictionary JsonGameLoader::GetPlayerInventory(const string &saveName) {
    return GetData(SAVES_DIR + saveName + PLAYER_INVENTORY_FILE);
}

JsonDictionary JsonGameLoader::GetPlayerEquipments(const string &saveName) {
    return GetData(SAVES_DIR + saveName + PLAYER_EQUIPMENTS_FILE);
}

JsonDictionary JsonGameLoader::GetPlayerSkills(const string &saveName) {
    return GetData(SAVES_DIR + saveName + PLAYER_SKILLS_FILE);
}

#pragma endregion

Player *JsonGameLoader::LoadPlayer(const string &saveName) {
    JsonDictionary playerData = GetSaveMetadata(saveName);
    JsonDictionary playerInventory = GetPlayerInventory(saveName);
    JsonDictionary playerEquipments = GetPlayerEquipments(saveName);
    JsonDictionary playerSkills = GetPlayerSkills(saveName);



    // Loading player's associated objects
    Map *playerMap = LoadMap(playerData["map"]);

    Weapon *playerWeapon = LoadWeapon(playerData["weapon"]["id"]);

    list<Equipment> playerEquipmentsList = list<Equipment>();
    for (auto equipment: playerEquipments) {
        playerEquipmentsList.push_back(LoadEquipment(equipment["id"]));
    }

    list<stack<Item>> playerInventoryList = list<stack<Item>>();
    for (auto item: playerInventory) {
        stack<Item> itemStack = stack<Item>();
        for (int i = 0; i < item["quantity"]; i++) {
            itemStack.push(LoadItem(item["id"]));
        }
        playerInventoryList.push_back(itemStack);
    }

    list<Skill> playerSkillsList = list<Skill>();
    for (auto skill: playerSkills) {
        playerSkillsList.push_back(LoadSkill(skill["id"]));
    }

    return new Player(playerData["id"], playerData["name"], playerMap, playerData["posX"],
                      playerData["posY"],playerWeapon, playerEquipmentsList,
                      playerInventoryList, playerSkillsList);
}

Map *JsonGameLoader::LoadMap(const string &mapName) {
    JsonDictionary mapData = GetData(MAPS_DIR + mapName + METADATA_FILE);

    return new Map(mapData["id"], mapData["name"], mapData["height"], mapData["width"]);
}

Weapon *JsonGameLoader::LoadWeapon(int weaponId) {
    JsonDictionary weapons = GetData(ASSETS_WEAPON_FILE);
    Weapon *weapon = nullptr;
    int index = 0;

    while (weapon == nullptr && index < weapons.size()) {
        if (weapons[index]["id"] == weaponId) {
            weapon = new Weapon(weapons[index]["id"], weapons[index]["name"],
                                weapons[index]["description"], weapons[index]["damage"],
                                weapons[index]["frequency"], weapons[index]["loadTime"],
                                weapons[index]["range"], weapons[index]["durability"]);
        }

        index++;
    }
    return weapon;
}

Equipment JsonGameLoader::LoadEquipment(int equipmentId) {
    JsonDictionary equipments = GetData(ASSETS_EQUIPMENT_FILE);
    Equipment *equipment = nullptr;
    int index = 0;

    while (equipment == nullptr && index < equipments.size()) {
        if (equipments[index]["id"] == equipmentId) {
            equipment = new Equipment(equipments[index]["id"], equipments[index]["name"],
                                      equipments[index]["description"],
                                      equipments[index]["damageAbsorption"],
                                      equipments[index]["durability"]);
        }

        index++;
    }

    if (equipment == nullptr) { // Should never be null in our context (this is open to criticism)
        throw EquipmentNotFound("Could not find any equipment with id: " + to_string(equipmentId));
    }

    return *equipment;
}

Item JsonGameLoader::LoadItem(int itemId) {
    // As equipments and weapons are also items, we want to create an instance of the right type, and send it back
    // contained in an Item container.
    // We can deduce the type based on the index: weapons ranges from 2000 to 2999; equipments from 3000 to 3999; while
    // actual items ranges from 1000 to 1999.
    Item *item = nullptr;

    if (itemId >= 2000 && itemId < 3000) { // It is a weapon
        item = LoadWeapon(itemId);
    } else if (itemId >= 3000 && itemId < 4000) { // It is an equipment
        Equipment equipment = LoadEquipment(itemId);
        item = &equipment;
    } else {
        JsonDictionary items = GetData(ASSETS_ITEM_FILE);
        int index = 0;

        while (item == nullptr && index < items.size()) {
            if (items[index]["id"] == itemId) {
                item = new Item(items[index]["id"], items[index]["name"], items[index]["description"]);
            }

            index++;
        }
    }

    if (item == nullptr) { // Should never be null in our context (this is open to criticism)
        throw ItemNotFound("Could not find any item with id: " + to_string(itemId));
    }

    return *item;
}

Skill JsonGameLoader::LoadSkill(int skillId) {
    JsonDictionary skills = GetData(ASSETS_SKILL_FILE);
    Skill *skill = nullptr;
    int index = 0;

    while (skill == nullptr && index < skills.size()) {
        if (skills[index]["id"] == skillId) {
            skill = new Skill(skills[index]["id"], skills[index]["name"],
                              skills[index]["description"]);
        }

        index++;
    }

    if (skill == nullptr) { // Should never be null in our context (this is open to criticism)
        throw SkillNotFound("Could not find any equipment with id: " + to_string(skillId));
    }

    return *skill;
}

JsonDictionary JsonGameLoader::GetData(const string &path) {
    ifstream f(path);
    if (!f.is_open()) {
        throw SaveNotFound("Could not find any save with the matching save name");
    }

    return JsonDictionary::parse(f);
}

void JsonGameLoader::ParseAndAffectGlobalVariables(Game *game, JsonDictionary jsonVariables) {
    game->Difficulty = static_cast<Difficulty>(jsonVariables["difficulty"]);
    game->ChoseClass = jsonVariables["choseClass"];
    game->ConqueredRedDungeon = static_cast<State>(jsonVariables["conqueredRedDungeon"]);
    game->CrossedThousandYearsForest = static_cast<State>(jsonVariables["crossedThousandYearsForest"]);
    game->ConqueredAbyssDungeon = static_cast<State>(jsonVariables["conqueredAbyssDungeon"]);
    game->StraightenedDawnKingdom = static_cast<State>(jsonVariables["straightenedDawnKingdom"]);
    game->ConqueredFinalDungeon = static_cast<State>(jsonVariables["conqueredFinalDungeon"]);
}

#pragma clang diagnostic pop