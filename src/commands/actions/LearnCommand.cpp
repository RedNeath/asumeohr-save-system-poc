//
// Created by redneath on 22/07/23.
//

#include "LearnCommand.h"


LearnCommand::LearnCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void LearnCommand::Execute(std::vector<std::string> args) {

}

LearnCommand::~LearnCommand() = default;
