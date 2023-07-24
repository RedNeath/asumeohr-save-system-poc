//
// Created by redneath on 22/07/23.
//

#include "TeleportCommand.h"


TeleportCommand::TeleportCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void TeleportCommand::Execute(std::vector<std::string> args) {

}

TeleportCommand::~TeleportCommand() = default;
