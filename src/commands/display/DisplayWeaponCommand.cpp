//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayWeaponCommand.h"

using namespace std;

DisplayWeaponCommand::DisplayWeaponCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void DisplayWeaponCommand::Execute(std::vector<std::string> args) {
    Weapon *weapon = Game->GetPlayer()->GetWeapon();
    if (weapon == nullptr) {
        cout << "No weapon equipped." << endl;
    } else {
        cout << weapon->ToString("") << endl;
    }
}

DisplayWeaponCommand::~DisplayWeaponCommand() = default;
