//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayMapCommand.h"

using namespace std;

DisplayMapCommand::DisplayMapCommand(class Game *Game) : ICommand(Game) {

}

void DisplayMapCommand::Execute(std::vector<std::string> args) {
    cout << Game->GetPlayer()->GetMap()->ToString("") << endl;
}

DisplayMapCommand::~DisplayMapCommand() = default;
