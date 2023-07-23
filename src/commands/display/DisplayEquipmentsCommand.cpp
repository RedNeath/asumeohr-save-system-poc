//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayEquipmentsCommand.h"

using namespace std;


DisplayEquipmentsCommand::DisplayEquipmentsCommand(class Game *Game) : ICommand(Game) {

}

void DisplayEquipmentsCommand::Execute(std::vector<std::string> args) {
    vector<Equipment*> playerEquipments = Game->GetPlayer()->GetEquipments();
    string output; // We do it this way so that the icons are displayed first and their display message doesn't get in the middle of the display of the equipments.
    int index = 1;

    for(auto item: playerEquipments) {
        output += "Equipment " + to_string(index) + ":\n";
        output += item->ToString("\t") + "\n";

        index++;
    }

    cout << output; // No need to put a new line, it is already at the end of the string.
}

DisplayEquipmentsCommand::~DisplayEquipmentsCommand() = default;
