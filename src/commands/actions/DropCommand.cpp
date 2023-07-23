//
// Created by redneath on 22/07/23.
//

#include "DropCommand.h"
#include "../../exceptions/NoMatchingSignature.h"

using namespace std;


DropCommand::DropCommand(class Game *Game) : ICommand(Game) {

}

void DropCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tdrop <inventory_slot:int> [quantity:int]\n" +
                                  "For more information, see the README.md file.");
    }

    int slot = GetIntegerArg(args[1]) - 1;
    int quantity = 1;
    vector<stack<Item*>*> inventory = Game->GetPlayer()->GetInventory();
    stack<Item*> *itemStack;

    // Checking the inventory slot
    if (slot < 0 || slot > inventory.size() - 1) {
        throw BadInputException("Bad input value for \"inventory_slot\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: An integer value between 1 and " +
                                to_string(inventory.size()) + ".");
    }

    // Getting the quantity, if given
    if (args.size() >= 3) {
        int quantityGiven = GetIntegerArg(args[2]);

        if (quantityGiven < 1 || quantityGiven > inventory[slot]->size()) {
            throw BadInputException("Bad input value for \"quantity\":\n"
                                    "\tGiven: " + args[2] + "\n" +
                                    "\tExpected: An integer value between 1 and " +
                                    to_string(inventory[slot]->size()) + ".");
        }
        quantity = quantityGiven;
    }

    // To accomplish this task, we are going to pop the quantity specified out of the stack.
    // Once popped, we will check if the stack is empty, and if it is, we will remove the stack from the inventory.
    //
    // ⚠️ As the inventory and its stacks are not using any pointers, using them out does not actually affect the real
    //    player inventory, so we have to use the player's setter to change its actual inventory with the one modified
    //    here.
    itemStack = inventory[slot];
    for ( ; quantity > 0; quantity--) {
        Item* item = itemStack->top();
        itemStack->pop();

        delete item;
    }

    if (itemStack->empty()) {
        inventory.erase(inventory.begin() + slot);
        delete itemStack;
    }

    Game->GetPlayer()->SetInventory(inventory);
}

DropCommand::~DropCommand() = default;
