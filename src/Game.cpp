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
}

Game::~Game() {
    delete Player;
    delete Maps;
}

void Game::Play() {
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
        ICommand *command = GetCommand(tokens[0]);
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

    output  = "Player data:\n";
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

std::vector<std::string> Game::ParseCommandTokens(const std::string &input) {
    stringstream ss(input);
    vector<string> tokens;

    for (string w; ss>>w; ) {
        tokens.push_back(w);
    }

    return tokens;
}

ICommand *Game::GetCommand(const string &commandName) {
    ICommand *command;
    auto commandEnum = CommandNames.find(commandName);

    if (commandEnum == CommandNames.end()) {
        throw CommandNotFoundException("No such command: \"" + commandName + "\".");
    }

    switch(commandEnum->second) {
        case Commands::SAVE:
            command = new SaveCommand(this);
            break;

        case Commands::SAVE_EXIT:
            command = new SaveAndExitCommand(this);
            break;

        case Commands::EXIT:
            command = new ExitCommand(this);
            break;

        case Commands::GIVE:
            command = new GiveCommand(this);
            break;

        case Commands::DROP:
            command = new DropCommand(this);
            break;

        case Commands::EQUIP:
            command = new EquipCommand(this);
            break;

        case Commands::UNEQUIP:
            command = new UnequipCommand(this);
            break;

        case Commands::LEARN:
            command = new LearnCommand(this);
            break;

        case Commands::FORGET:
            command = new ForgetCommand(this);
            break;

        case Commands::MOVE:
            command = new MoveCommand(this);
            break;

        case Commands::TELEPORT:
            command = new TeleportCommand(this);
            break;

        case Commands::SET_DIFFICULTY:
            command = new SetDifficultyCommand(this);
            break;

        case Commands::TOGGLE_CHOSE_CLASS:
            command = new ToggleChoseClassCommand(this);
            break;

        case Commands::PROGRESS:
            command = new ProgressCommand(this);
            break;

        case Commands::DISPLAY:
            command = new DisplayAllCommand(this);
            break;

        case Commands::DISPLAY_PLAYER:
            command = new DisplayPlayerCommand(this);
            break;

        case Commands::DISPLAY_MAP_CACHE:
            command = new DisplayMapCacheCommand(this);
            break;

        case Commands::DISPLAY_WEAPON:
            command = new DisplayWeaponCommand(this);
            break;

        case Commands::DISPLAY_EQUIPMENTS:
            command = new DisplayEquipmentsCommand(this);
            break;

        case Commands::DISPLAY_INVENTORY:
            command = new DisplayInventoryCommand(this);
            break;

        case Commands::DISPLAY_SKILLS:
            command = new DisplaySkillsCommand(this);
            break;

        case Commands::DISPLAY_MAP:
            command = new DisplayMapCommand(this);
            break;

    }

    return command;
}
