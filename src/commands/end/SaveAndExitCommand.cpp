//
// Created by redneath on 22/07/23.
//

#include "SaveAndExitCommand.h"


SaveAndExitCommand::SaveAndExitCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void SaveAndExitCommand::Execute(std::vector<std::string> args) {

}

SaveAndExitCommand::~SaveAndExitCommand() = default;
