//
// Created by redneath on 21/07/23.
//

#include "SaveCommand.h"


SaveCommand::SaveCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void SaveCommand::Execute(std::vector<std::string> args) {

}

SaveCommand::~SaveCommand() = default;
