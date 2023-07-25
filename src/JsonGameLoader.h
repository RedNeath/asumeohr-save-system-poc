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
    static std::string ASSETS_ICONS_DIR;
    static std::string MAPS_DIR;

    Game *LoadDataAndAssets(GameSettings settings) override;
    Item *GetItem(int itemId) override;
    Weapon *GetWeapon(int weaponId) override;
    Equipment *GetEquipment(int equipmentId) override;
    Skill *GetSkill(int skillId) override;
    Map *LoadMap(const std::string &mapName) override;

    void SaveData(Game *game, const std::string &saveName) override;

    Weapon *LoadWeapon(const JsonDictionary &json);
    std::vector<Equipment*> LoadEquipments(const JsonDictionary &json);
    std::vector<std::stack<Item*>*> LoadInventory(const JsonDictionary &json);
    std::vector<Skill*> LoadSkills(const JsonDictionary &json);

private:
    const std::string SAVES_DIR = "../data/json_implementation/saves/";
    const std::string ASSETS_WEAPON_FILE = "../data/json_implementation/assets/weapons.json";
    const std::string ASSETS_EQUIPMENT_FILE = "../data/json_implementation/assets/equipments.json";
    const std::string ASSETS_ITEM_FILE = "../data/json_implementation/assets/items.json";
    const std::string ASSETS_SKILL_FILE = "../data/json_implementation/assets/skills.json";
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

    void ParseAndAffectGlobalVariables(Game *game, JsonDictionary jsonVariables);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_JSONGAMELOADER_H
