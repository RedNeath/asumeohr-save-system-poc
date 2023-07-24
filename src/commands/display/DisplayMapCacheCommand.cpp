//
// Created by redneath on 22/07/23.
//

#include "DisplayMapCacheCommand.h"
#include "../../exceptions/NotImplementedException.h"


DisplayMapCacheCommand::DisplayMapCacheCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void DisplayMapCacheCommand::Execute(std::vector<std::string> args) {
    throw NotImplementedException("The command \"" + args[0] + "\" has not been implemented yet.");
}

DisplayMapCacheCommand::~DisplayMapCacheCommand() = default;
