//
// Created by redneath on 22/07/23.
//

#include "UnequipCommand.h"


UnequipCommand::UnequipCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void UnequipCommand::Execute(std::vector<std::string> args) {

}

UnequipCommand::~UnequipCommand() = default;
