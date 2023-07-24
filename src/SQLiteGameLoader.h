//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H


#include "IGameLoader.h"

class SQLiteGameLoader: public IGameLoader {
public:
    Game *LoadDataAndAssets(GameSettings settings) override;
    Item *GetItem(int itemId) override;
    Weapon *GetWeapon(int weaponId) override;
    Equipment *GetEquipment(int equipmentId) override;
    Skill *GetSkill(int skillId) override;
    Map *LoadMap(const std::string &mapName) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SQLITEGAMELOADER_H
