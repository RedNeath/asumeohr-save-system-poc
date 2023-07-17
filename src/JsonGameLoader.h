//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_JSONGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_JSONGAMELOADER_H

#include "nlohmann/json.hpp"
#include "IGameLoader.h"

using JsonDictionary = nlohmann::json;

class JsonGameLoader: public IGameLoader {
public:
    Game *LoadDataAndAssets(GameSettings settings) override;

private:
    const std::string SAVES_DIR = "../data/json_implementation/saves/";
    const std::string MAPS_DIR = "../data/json_implementation/maps/";
    const std::string ASSETS_WEAPON_FILE = "../data/json_implementation/weapons.json";
    const std::string ASSETS_EQUIPMENT_FILE = "../data/json_implementation/equipments.json";
    const std::string ASSETS_ITEM_FILE = "../data/json_implementation/items.json";
    const std::string ASSETS_SKILL_FILE = "../data/json_implementation/skills.json";
    const std::string METADATA_FILE = "/metadata.json";
    const std::string PLAYER_EQUIPMENTS_FILE = "/equipments.json";
    const std::string PLAYER_INVENTORY_FILE = "/inventory.json";
    const std::string PLAYER_SKILLS_FILE = "/skills.json";
    const std::string SAVE_GLOBAL_VARIABLES = "/global.json";

    // Get Json methods
    JsonDictionary GetData(const std::string &path);
    JsonDictionary GetSaveMetadata(const std::string &saveName);
    JsonDictionary GetPlayerInventory(const std::string &saveName);
    JsonDictionary GetPlayerEquipments(const std::string &saveName);
    JsonDictionary GetPlayerSkills(const std::string &saveName);

    // Loading methods
    Player *LoadPlayer(const std::string &saveName);
    Map *LoadMap(const std::string &mapName);
    Weapon *LoadWeapon(int weaponId);
    Equipment LoadEquipment(int equipmentId);
    Item LoadItem(int itemId);
    Skill LoadSkill(int skillId);

    void ParseAndAffectGlobalVariables(Game *game, JsonDictionary jsonVariables);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_JSONGAMELOADER_H
