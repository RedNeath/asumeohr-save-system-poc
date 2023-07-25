//
// Created by redneath on 22/07/23.
//

#include "SaveAndExitCommand.h"
#include "SaveCommand.h"
#include "ExitCommand.h"


SaveAndExitCommand::SaveAndExitCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void SaveAndExitCommand::Execute(std::vector<std::string> args) {
    SaveCommand save = SaveCommand(Game, GameLoader);
    ExitCommand exit = ExitCommand(Game, GameLoader);

    save.Execute(args);
    exit.Execute({"inner_execute"});
}

SaveAndExitCommand::~SaveAndExitCommand() = default;
