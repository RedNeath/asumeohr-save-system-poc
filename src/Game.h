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
#include "interfaces/ICommand.h"
#include "enums/Commands.h"

class Game {
private:
    bool Exited;
    class Player *Player;
    HeavyResourcesCache<Map> *Maps;
    std::string Prompt;
#pragma region Command map

    const std::unordered_map<std::string,Commands> CommandNames = {
            {"save", Commands::SAVE},
            {"save_exit", Commands::SAVE_EXIT},
            {"exit", Commands::EXIT},
            {"give", Commands::GIVE},
            {"drop", Commands::DROP},
            {"equip", Commands::EQUIP},
            {"unequip", Commands::UNEQUIP},
            {"learn", Commands::LEARN},
            {"forget", Commands::FORGET},
            {"move", Commands::MOVE},
            {"teleport", Commands::TELEPORT},
            {"set_difficulty", Commands::SET_DIFFICULTY},
            {"toggle_chose_class", Commands::TOGGLE_CHOSE_CLASS},
            {"progress", Commands::PROGRESS},
            {"display", Commands::DISPLAY},
            {"display_player", Commands::DISPLAY_PLAYER},
            {"display_map_cache", Commands::DISPLAY_MAP_CACHE},
            {"display_weapon", Commands::DISPLAY_WEAPON},
            {"display_equipments", Commands::DISPLAY_EQUIPMENTS},
            {"display_inventory", Commands::DISPLAY_INVENTORY},
            {"display_skills", Commands::DISPLAY_SKILLS},
            {"display_map", Commands::DISPLAY_MAP}
    };

#pragma endregion Command map
#pragma region Global state variables map

    std::unordered_map<std::string, State*> GlobalStateVariables = {};

#pragma endregion Global state variables map

    std::vector<std::string> ParseCommandTokens(const std::string &input);
    class ICommand *GetCommand(const std::string &commandName);

public:
    // Game parameters
    enum Difficulty Difficulty;
    bool ChoseClass;
    State *ConqueredRedDungeon;
    State *CrossedThousandYearsForest;
    State *ConqueredAbyssDungeon;
    State *StraightenedDawnKingdom;
    State *ConqueredFinalDungeon;

    std::string SaveName;

    Game(class Player *player, HeavyResourcesCache<Map> *maps, const std::string &saveName);
    ~Game();

    /**
     * In a normal game, this method would be looped 60 times per second, but in
     * our case, it serves only as a command invoker.
     *
     * Since there is nothing to refresh 60 times per minute in our terminal, we
     * can keep it frozen until a new command is entered.
     */
    void Play();

    // Getters
    class Player *GetPlayer() const;
    HeavyResourcesCache<Map> *GetMaps() const;

    // Setters
    void SetPlayer(class Player *player);
    void SetMaps(HeavyResourcesCache<Map> *maps);

    std::string ToString(const std::string &t);
    void Exit();
    bool HasEnded() const;
    State *GetState(const std::string &variableName);
    std::string GetStatesMapToString(const std::string &t);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GAME_H
