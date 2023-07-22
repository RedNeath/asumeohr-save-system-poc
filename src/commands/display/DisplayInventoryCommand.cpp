//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayInventoryCommand.h"

using namespace std;

DisplayInventoryCommand::DisplayInventoryCommand(class Game *Game) : ICommand(Game) {

}

void DisplayInventoryCommand::Execute(std::vector<std::string> args) {
    list<stack<Item>> playerInventory = Game->GetPlayer()->GetInventory();
    string output; // See DisplayEquipmentsCommand
    int index = 1;

    for (auto it = playerInventory.begin(); it != playerInventory.end(); ++it) {
        output += "Item stack " + to_string(index) + ":\n";
        output += it->top().ToString("\t") + "\n";
        output += "\tQuantity: " + to_string(it->size()) + "\n";

        index++;
    }

    cout << output;
}

DisplayInventoryCommand::~DisplayInventoryCommand() = default;
