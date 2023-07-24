//
// Created by redneath on 16/07/23.
//

#include <iostream>
#include "Game.h"
#include "exceptions/CommandNotFoundException.h"
#include "commands/end/SaveCommand.h"
#include "commands/end/SaveAndExitCommand.h"
#include "commands/end/ExitCommand.h"
#include "commands/actions/GiveCommand.h"
#include "commands/actions/DropCommand.h"
#include "commands/actions/EquipCommand.h"
#include "commands/actions/UnequipCommand.h"
#include "commands/actions/LearnCommand.h"
#include "commands/actions/ForgetCommand.h"
#include "commands/actions/MoveCommand.h"
#include "commands/actions/TeleportCommand.h"
#include "commands/settings/SetDifficultyCommand.h"
#include "commands/settings/ToggleChoseClassCommand.h"
#include "commands/settings/ProgressCommand.h"
#include "commands/display/DisplayAllCommand.h"
#include "commands/display/DisplayPlayerCommand.h"
#include "commands/display/DisplayMapCacheCommand.h"
#include "commands/display/DisplayWeaponCommand.h"
#include "commands/display/DisplayEquipmentsCommand.h"
#include "commands/display/DisplayInventoryCommand.h"
#include "commands/display/DisplaySkillsCommand.h"
#include "commands/display/DisplayMapCommand.h"

using namespace std;

Game::Game(class Player *player, HeavyResourcesCache<Map> *maps, const std::string &saveName) {
    Player = player;
    Maps = maps;
    SaveName = saveName;

    Exited = false;
    Prompt = "\x1B[1;32m" + player->GetName() + "@POC-Game\033[0m:\x1B[1;34m" + SaveName + "\033[0m$ ";

    // Initialise state global variables
    ConqueredRedDungeon = new State();
    CrossedThousandYearsForest = new State();
    ConqueredAbyssDungeon = new State();
    StraightenedDawnKingdom = new State();
    ConqueredFinalDungeon = new State();

    GlobalStateVariables = {
            {"ConqueredRedDungeon", ConqueredRedDungeon},
            {"CrossedThousandYearsForest", CrossedThousandYearsForest},
            {"ConqueredAbyssDungeon", ConqueredAbyssDungeon},
            {"StraightenedDawnKingdom", StraightenedDawnKingdom},
            {"ConqueredFinalDungeon", ConqueredFinalDungeon}
    };
}

Game::~Game() {
    delete Player;
    delete Maps;

    delete ConqueredRedDungeon;
    delete CrossedThousandYearsForest;
    delete ConqueredAbyssDungeon;
    delete StraightenedDawnKingdom;
    delete ConqueredFinalDungeon;
}

void Game::Play(IGameLoader *gameLoader) {
    // We will take the user input, parse it into tokens, find and instantiate
    // the associated command(s) and execute them.
    string input;

    cout << Prompt;
    getline(cin, input);

    auto tokens = ParseCommandTokens(input);

    // If there is no input we simply display a new line. This is not an error
    if (tokens.empty()) {
        return;
    }

    try {
        ICommand *command = GetCommand(tokens[0], gameLoader);
        command->Execute(tokens);

        // freeing the memory
        delete command;
    } catch (runtime_error &e) {
        cout << e.what() << endl;
    }
}

Player *Game::GetPlayer() const {
    return Player;
}

HeavyResourcesCache<Map> *Game::GetMaps() const {
    return Maps;
}

void Game::SetPlayer(class Player *player) {
    Player = player;
}

void Game::SetMaps(HeavyResourcesCache<Map> *maps) {
    Maps = maps;
}

string Game::ToString(const string &t) {
    string output;

    output  = "\nGame variables:\n";
    output += "\tDifficulty:                    " + to_string((int) Difficulty) + "\n";
    output += "\tChoseClass:                    " + to_string(ChoseClass) + "\n";
    output += "\tConqueredRedDungeon:           " + to_string((int) *ConqueredRedDungeon) + "\n";
    output += "\tCrossedThousandYearsForest:    " + to_string((int) *CrossedThousandYearsForest) + "\n";
    output += "\tConqueredAbyssDungeon:         " + to_string((int) *ConqueredAbyssDungeon) + "\n";
    output += "\tStraightenedDawnKingdom:       " + to_string((int) *StraightenedDawnKingdom) + "\n";
    output += "\tConqueredFinalDungeon:         " + to_string((int) *ConqueredFinalDungeon) + "\n\n";

    output += "Player data:\n";
    output +=  Player->ToString(t + "\t") + "\n";

    //TODO
    //output += "Maps cache data:\n";
    //output +=  Maps->ToString(t + "\t");

    return output;
}

void Game::Exit() {
    Exited = true;
}

bool Game::HasEnded() const {
    return Exited;
}

State *Game::GetState(const string &variableName) {
    State *variable;
    auto variablePair = GlobalStateVariables.find(variableName);

    if (variablePair == GlobalStateVariables.end()) {
        return nullptr;
    }

    return variablePair->second;
}

std::string Game::GetStatesMapToString(const string &t) {
    string output;

    for (auto it = GlobalStateVariables.begin(); it != GlobalStateVariables.end(); ++it) {
        output += t + "- " + it->first + "\n";
    }

    return output;
}

std::vector<std::string> Game::ParseCommandTokens(const std::string &input) {
    stringstream ss(input);
    vector<string> tokens;

    for (string w; ss>>w; ) {
        tokens.push_back(w);
    }

    return tokens;
}

ICommand *Game::GetCommand(const string &commandName, IGameLoader *gameLoader) {
    ICommand *command;
    auto commandEnum = CommandNames.find(commandName);

    if (commandEnum == CommandNames.end()) {
        throw CommandNotFoundException("No such command: \"" + commandName + "\".");
    }

    switch(commandEnum->second) {
        case Command::SAVE:
            command = new SaveCommand(this, gameLoader);
            break;

        case Command::SAVE_EXIT:
            command = new SaveAndExitCommand(this, gameLoader);
            break;

        case Command::EXIT:
            command = new ExitCommand(this, gameLoader);
            break;

        case Command::GIVE:
            command = new GiveCommand(this, gameLoader);
            break;

        case Command::DROP:
            command = new DropCommand(this, gameLoader);
            break;

        case Command::EQUIP:
            command = new EquipCommand(this, gameLoader);
            break;

        case Command::UNEQUIP:
            command = new UnequipCommand(this, gameLoader);
            break;

        case Command::LEARN:
            command = new LearnCommand(this, gameLoader);
            break;

        case Command::FORGET:
            command = new ForgetCommand(this, gameLoader);
            break;

        case Command::MOVE:
            command = new MoveCommand(this, gameLoader);
            break;

        case Command::TELEPORT:
            command = new TeleportCommand(this, gameLoader);
            break;

        case Command::SET_DIFFICULTY:
            command = new SetDifficultyCommand(this, gameLoader);
            break;

        case Command::TOGGLE_CHOSE_CLASS:
            command = new ToggleChoseClassCommand(this, gameLoader);
            break;

        case Command::PROGRESS:
            command = new ProgressCommand(this, gameLoader);
            break;

        case Command::DISPLAY:
            command = new DisplayAllCommand(this, gameLoader);
            break;

        case Command::DISPLAY_PLAYER:
            command = new DisplayPlayerCommand(this, gameLoader);
            break;

        case Command::DISPLAY_MAP_CACHE:
            command = new DisplayMapCacheCommand(this, gameLoader);
            break;

        case Command::DISPLAY_WEAPON:
            command = new DisplayWeaponCommand(this, gameLoader);
            break;

        case Command::DISPLAY_EQUIPMENTS:
            command = new DisplayEquipmentsCommand(this, gameLoader);
            break;

        case Command::DISPLAY_INVENTORY:
            command = new DisplayInventoryCommand(this, gameLoader);
            break;

        case Command::DISPLAY_SKILLS:
            command = new DisplaySkillsCommand(this, gameLoader);
            break;

        case Command::DISPLAY_MAP:
            command = new DisplayMapCommand(this, gameLoader);
            break;

    }

    return command;
}
