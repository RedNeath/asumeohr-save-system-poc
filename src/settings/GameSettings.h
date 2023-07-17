//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H
#define ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H


/**
 * This class contains the game settings (by reading the properties in data/game_settings.json)
 */
class GameSettings {
public:
    std::string SaveName;
    int MapCacheSize;

    GameSettings();
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H
