//
// Created by redneath on 22/07/23.
//

#include "ExitCommand.h"


ExitCommand::ExitCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void ExitCommand::Execute(std::vector<std::string> args) {
    Game->Exit();
}

ExitCommand::~ExitCommand() = default;
