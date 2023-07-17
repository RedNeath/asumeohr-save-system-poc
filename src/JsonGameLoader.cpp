#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
//
// Created by redneath on 16/07/23.
//

#include <fstream>
#include "nlohmann/json.hpp"
#include "JsonGameLoader.h"
#include "exceptions/SaveNotFound.h"

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

Map *JsonGameLoader::LoadMap(const string &mapName) {
    JsonDictionary mapData = GetData(MAPS_DIR + mapName + METADATA_FILE);

    return new Map(mapData["id"], mapData["name"], mapData["height"], mapData["width"]);
}

Weapon *JsonGameLoader::LoadWeapon(const JsonDictionary &json) {
    JsonDictionary weapons = GetData(ASSETS_WEAPON_FILE);
    Weapon *weapon = nullptr;
    int weaponId;
    int durabilityLeft;

    json.at("id").get_to(weaponId);
    json.at("durabilityLeft").get_to(durabilityLeft);

    for (auto &elem: weapons) {
        int elemId;
        elem.at("id").get_to(elemId);

        if (elemId == weaponId) {
            weapon = new Weapon(elem);
        }

        if (weapon != nullptr) {
            // We found it, we just need to add the durability left
            weapon->SetDurabilityLeft(durabilityLeft);
        }
    }

    return weapon;
}

list<Equipment> JsonGameLoader::LoadEquipments(const JsonDictionary &json) {
    JsonDictionary equipments = GetData(ASSETS_EQUIPMENT_FILE);
    list<Equipment> playerEquipments = list<Equipment>();

    for (auto &elem: equipments) {
        int elemId;
        elem.at("id").get_to(elemId);

        for (auto &playerEquipment: json) {
            Equipment *equipment = nullptr;
            int id;
            int durabilityLeft;

            playerEquipment.at("id").get_to(id);
            playerEquipment.at("durabilityLeft").get_to(durabilityLeft);

            if (id == elemId) {
                equipment = new Equipment(elem);
            }

            if (equipment != nullptr) {
                equipment->SetDurabilityLeft(durabilityLeft);
                playerEquipments.push_back(*equipment);
            }
        }
    }

    return playerEquipments;
}

list<stack<Item>> JsonGameLoader::LoadInventory(const JsonDictionary &json) {
    // As equipments and weapons are also items, we want to create an instance of the right type, and send it back
    // contained in an Item container.
    // We can deduce the type based on the index: weapons ranges from 2000 to 2999; equipments from 3000 to 3999; while
    // actual items ranges from 1000 to 1999.
    list<stack<Item>> playerInventory = list<stack<Item>>();
    list<JsonDictionary> actualItems = list<JsonDictionary>();

    for (auto &item: json) {
        int itemId;
        int quantity;

        item.at("item").get_to(itemId);
        item.at("quantity").get_to(quantity);

        if (itemId >= 2000 && itemId < 3000) { // It is a weapon
            int durabilityLeft;
            JsonDictionary weaponJson;

            item.at("durabilityLeft").get_to(durabilityLeft);
            weaponJson = JsonDictionary::parse("{\"id\": " + to_string(itemId) + ", \"durabilityLeft\": " +
                    to_string(durabilityLeft) + "}");

            stack<Item> weaponStack = stack<Item>();

            for (int i = 0; i < quantity; i++) {
                weaponStack.push(*LoadWeapon(weaponJson));
            }

            playerInventory.push_back(weaponStack);
        } else if (itemId >= 3000 && itemId < 4000) { // It is an equipment
            int durabilityLeft;
            JsonDictionary equipmentJson;

            item.at("durabilityLeft").get_to(durabilityLeft);
            equipmentJson = JsonDictionary::parse("[{\"id\": " + to_string(itemId) + ", \"durabilityLeft\": " +
                                                  to_string(durabilityLeft) + "}]");

            stack<Item> equipmentStack = stack<Item>();

            for (int i = 0; i < quantity; i++) {
                equipmentStack.push(LoadEquipments(equipmentJson).front());
            }

            playerInventory.push_back(equipmentStack);
        } else {
            actualItems.push_back(item);
        }
    }

    // Now we retrieved the weapons and equipments. The only things left to retrieve are actual items.
    JsonDictionary items = GetData(ASSETS_ITEM_FILE);

    for (auto &elem: items) {
        int elemId;
        elem.at("id").get_to(elemId);

        for (auto &playerItem: actualItems) {
            Item *item;
            int id;
            int quantity;

            playerItem.at("item").get_to(id);
            playerItem.at("quantity").get_to(quantity);

            if (id == elemId) {
                stack<Item> itemsStack = stack<Item>();

                for (int i = 0; i < quantity; i++) {
                    itemsStack.emplace(elem);
                }

                playerInventory.push_back(itemsStack);
            }
        }
    }

    return playerInventory;
}

list<Skill> JsonGameLoader::LoadSkills(const JsonDictionary &json) {
    JsonDictionary skills = GetData(ASSETS_SKILL_FILE);
    list<Skill> playerSkills = list<Skill>();

    for (auto &elem: skills) {
        int elemId;
        elem.at("id").get_to(elemId);

        for (auto &playerSkill: json) {
            Skill *skill = nullptr;
            int id;

            playerSkill.get_to(id);

            if (id == elemId) {
                playerSkills.emplace_back(elem);
            }
        }
    }

    return playerSkills;
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
    JsonDictionary metadata = GetSaveMetadata(saveName);
    JsonDictionary inventory = GetPlayerInventory(saveName);
    JsonDictionary equipments = GetPlayerEquipments(saveName);
    JsonDictionary skills = GetPlayerSkills(saveName);

    return new Player(this, metadata, equipments, inventory, skills);
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