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
#include "enums/Command.h"


class IGameLoader;

class Game {
private:
    bool Exited;
    class Player *Player;
    HeavyResourcesCache<Map> *Maps;
    std::string Prompt;
#pragma region Command map

    const std::unordered_map<std::string,Command> CommandNames = {
            {"save",               Command::SAVE},
            {"save_exit",          Command::SAVE_EXIT},
            {"exit",               Command::EXIT},
            {"give",               Command::GIVE},
            {"drop",               Command::DROP},
            {"equip",              Command::EQUIP},
            {"unequip",            Command::UNEQUIP},
            {"learn",              Command::LEARN},
            {"forget",             Command::FORGET},
            {"move",               Command::MOVE},
            {"teleport",           Command::TELEPORT},
            {"set_difficulty",     Command::SET_DIFFICULTY},
            {"toggle_chose_class", Command::TOGGLE_CHOSE_CLASS},
            {"progress",           Command::PROGRESS},
            {"display",            Command::DISPLAY},
            {"display_player",     Command::DISPLAY_PLAYER},
            {"display_map_cache",  Command::DISPLAY_MAP_CACHE},
            {"display_weapon",     Command::DISPLAY_WEAPON},
            {"display_equipments", Command::DISPLAY_EQUIPMENTS},
            {"display_inventory",  Command::DISPLAY_INVENTORY},
            {"display_skills",     Command::DISPLAY_SKILLS},
            {"display_map",        Command::DISPLAY_MAP}
    };

#pragma endregion Command map
#pragma region Global state variables map

    std::unordered_map<std::string, State*> GlobalStateVariables = {};

#pragma endregion Global state variables map

    std::vector<std::string> ParseCommandTokens(const std::string &input);
    class ICommand *GetCommand(const std::string &commandName, IGameLoader *gameLoader);

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
    void Play(IGameLoader *gameLoader);

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

    JsonDictionary GetGlobalsAsJson();
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GAME_H
