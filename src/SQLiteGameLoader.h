//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H

#include <sqlite3.h>
#include "../lib/sqlite_modern_cpp.h"
#include "IGameLoader.h"

class SQLiteGameLoader: public IGameLoader {
private:
    const std::string DB_PATH = "../data/sqlite_implementation/game_data.db";

    Player *LoadPlayer(const std::string &saveName, sqlite::database db);
    void LoadAndAffectGlobalVariables(Game *game, sqlite::database db);
    Map *LoadMap(int mapId, sqlite::database db);
    Weapon *LoadWeapon(Player *player, sqlite::database db);
    std::vector<Equipment*> LoadEquipments(Player *player, sqlite::database db);
    std::vector<std::stack<Item*>*> LoadInventory(Player *player, sqlite::database db);
    std::vector<Skill*> LoadSkills(Player *player, sqlite::database db);
    int GetGlobalValue(const std::string &variableName, Player *player, sqlite::database db);
    int WashSaveDataAndGetPlayerId(const std::string &saveName, sqlite::database *db);
    int LastPlayerId(sqlite::database *db);
    int LastGlobalVariableId(sqlite::database *db);
    void SaveEquipments(Player *player, sqlite::database *db);
    void SaveGlobalVariables(Game *game, sqlite::database *db);
    void SaveInventory(Player *player, sqlite::database *db);
    void SavePlayerMetadata(Player *player, const std::string &saveName, sqlite::database *db);
    void SaveSkills(Player *player, sqlite::database *db);
public:
    Game *LoadDataAndAssets(GameSettings settings) override;
    Item *GetItem(int itemId) override;
    Weapon *GetWeapon(int weaponId) override;
    Equipment *GetEquipment(int equipmentId) override;
    Skill *GetSkill(int skillId) override;
    Map *LoadMap(const std::string &mapName) override;

    void SaveData(Game *game, const std::string &saveName) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
