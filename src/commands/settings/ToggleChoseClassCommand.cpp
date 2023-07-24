//
// Created by redneath on 22/07/23.
//

#include "ToggleChoseClassCommand.h"


ToggleChoseClassCommand::ToggleChoseClassCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void ToggleChoseClassCommand::Execute(std::vector<std::string> args) {
    Game->ChoseClass = !Game->ChoseClass; // As simple as that :D
}

ToggleChoseClassCommand::~ToggleChoseClassCommand() = default;
