//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayAllCommand.h"

using namespace std;


DisplayAllCommand::DisplayAllCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void DisplayAllCommand::Execute(std::vector<std::string> args) {
    cout << Game->ToString("") << endl;
}

DisplayAllCommand::~DisplayAllCommand() = default;
