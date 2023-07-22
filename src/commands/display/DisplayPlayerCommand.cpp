//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayPlayerCommand.h"

using namespace std;

DisplayPlayerCommand::DisplayPlayerCommand(class Game *Game) : ICommand(Game) {

}

void DisplayPlayerCommand::Execute(std::vector<std::string> args) {
    cout << Game->GetPlayer()->ToString("") << endl;
}

DisplayPlayerCommand::~DisplayPlayerCommand() = default;
