//
// Created by redneath on 21/07/23.
//

#include "SaveCommand.h"
#include "../../IGameLoader.h"


SaveCommand::SaveCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void SaveCommand::Execute(std::vector<std::string> args) {
    if (args.size() > 1) {
        GameLoader->SaveData(Game, args[1]);
    } else {
        GameLoader->SaveData(Game, Game->SaveName);
    }
}

SaveCommand::~SaveCommand() = default;
