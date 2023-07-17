//
// Created by redneath on 16/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_GAME_H
#define ASUMEOHR_SAVE_SYSTEM_POC_GAME_H


#include "cache/HeavyResourcesCache.h"
#include "entities/Map.h"
#include "entities/Player.h"
#include "enums/Difficulty.h"
#include "enums/State.h"

class Game {
private:
    class Player *Player;
    HeavyResourcesCache<Map> *Maps;

public:
    // Game parameters
    enum Difficulty Difficulty;
    bool ChoseClass;
    State ConqueredRedDungeon;
    State CrossedThousandYearsForest;
    State ConqueredAbyssDungeon;
    State StraightenedDawnKingdom;
    State ConqueredFinalDungeon;

    Game(class Player *player, HeavyResourcesCache<Map> *maps);
    ~Game();

    /**
     * The method to loop 60 times per minute (this is where everything will be computed).
     */
    void Play();

    // Getters
    class Player *GetPlayer() const;
    HeavyResourcesCache<Map> *GetMaps() const;

    // Setters
    void SetPlayer(class Player *player);
    void SetMaps(HeavyResourcesCache<Map> *maps);

    std::string ToString(const std::string &t);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GAME_H
