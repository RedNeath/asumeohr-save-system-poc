//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H


#include "Game.h"
#include "settings/GameSettings.h"

class IGameLoader {
public:
    virtual ~IGameLoader() = default;

    /**
     * Method that will load all the necessary data and assets of the game.
     *
     * @return The instance of game corresponding, ready to be played.
     */
    virtual Game *LoadDataAndAssets(GameSettings settings) = 0;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_IGAMELOADER_H
