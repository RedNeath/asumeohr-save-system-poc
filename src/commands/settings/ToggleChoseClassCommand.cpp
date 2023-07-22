//
// Created by redneath on 22/07/23.
//

#include "ToggleChoseClassCommand.h"


ToggleChoseClassCommand::ToggleChoseClassCommand(class Game *Game) : ICommand(Game) {

}

void ToggleChoseClassCommand::Execute(std::vector<std::string> args) {
    Game->ChoseClass = !Game->ChoseClass; // As simple as that :D
}

ToggleChoseClassCommand::~ToggleChoseClassCommand() = default;
