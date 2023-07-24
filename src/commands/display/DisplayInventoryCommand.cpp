//
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplayInventoryCommand.h"

using namespace std;

DisplayInventoryCommand::DisplayInventoryCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void DisplayInventoryCommand::Execute(std::vector<std::string> args) {
    vector<stack<Item*>*> playerInventory = Game->GetPlayer()->GetInventory();
    string output; // See DisplayEquipmentsCommand
    int index = 1;

    for (auto itemStack: playerInventory) {
        output += "Item stack " + to_string(index) + ":\n";
        output += itemStack->top()->ToString("\t") + "\n";
        output += "\tQuantity: " + to_string(itemStack->size()) + "\n";

        index++;
    }

    cout << output;
}

DisplayInventoryCommand::~DisplayInventoryCommand() = default;
