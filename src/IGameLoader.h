//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H


#include "settings/GameSettings.h"
#include "Game.h"

class IGameLoader {
public:
    virtual ~IGameLoader() = default;

    /**
     * Method that will load all the necessary data and assets of the game.
     *
     * @return The instance of game corresponding, ready to be played.
     */
    virtual Game *LoadDataAndAssets(GameSettings settings) = 0;
    virtual Item *GetItem(int itemId) = 0;
    virtual Weapon *GetWeapon(int weaponId) = 0;
    virtual Equipment *GetEquipment(int equipmentId) = 0;
    virtual Skill *GetSkill(int skillId) = 0;

    virtual Map *LoadMap(const std::string &mapName) = 0;

    virtual void SaveData(Game *game, const std::string &saveName) = 0;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
