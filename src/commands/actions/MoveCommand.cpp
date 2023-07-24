//
// Created by redneath on 22/07/23.
//

#include "MoveCommand.h"


MoveCommand::MoveCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void MoveCommand::Execute(std::vector<std::string> args) {

}

MoveCommand::~MoveCommand() = default;
