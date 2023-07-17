//
// Created by redneath on 16/07/23.
//
#include <fstream>
#include "nlohmann/json.hpp"
#include "GameSettings.h"

using JsonDictionary = nlohmann::json;
using namespace std;

GameSettings::GameSettings() {
    // We read from the game_settings file and return an object containing all the values we need.
    ifstream f("../data/game_settings.json");
    JsonDictionary data = JsonDictionary::parse(f);

    MapCacheSize = data["mapCacheSize"];
}
