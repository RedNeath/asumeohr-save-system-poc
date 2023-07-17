//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H
#define ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H

#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;

/**
 * This class contains the game settings (by reading the properties in data/game_settings.json)
 */
class GameSettings {
public:
    std::string SaveName;
    int MapCacheSize;

    GameSettings();
    static void to_json(JsonDictionary &json, const GameSettings &gameSettings);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GAMESETTINGS_H
