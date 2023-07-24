//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayWeaponCommand.h"

using namespace std;

DisplayWeaponCommand::DisplayWeaponCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void DisplayWeaponCommand::Execute(std::vector<std::string> args) {
    cout << Game->GetPlayer()->GetWeapon()->ToString("") << endl;
}

DisplayWeaponCommand::~DisplayWeaponCommand() = default;
