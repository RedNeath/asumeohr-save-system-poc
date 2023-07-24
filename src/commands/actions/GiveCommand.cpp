//
// Created by redneath on 22/07/23.
//

#include "GiveCommand.h"
#include "../../exceptions/NoMatchingSignature.h"
#include "../../IGameLoader.h"

using namespace std;

GiveCommand::GiveCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void GiveCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tgive <item_id:int> [quantity:int]\n" +
                                  "For more information, see the README.md file.");
    }

    int itemId = GetIntegerArg(args[1]);
    int quantity = 1;
    vector<stack<Item*>*> inventory = Game->GetPlayer()->GetInventory();
    stack<Item*> *itemStack = nullptr;

    // Checking the item id is correct
    if (itemId < 1000 || itemId > 3999) {
        throw BadInputException("Bad input value for \"item_id\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: An integer value between 1000 and 3999 (included).");
    }

    // Getting the quantity, if given
    if (args.size() >= 3) {
        int quantityGiven = GetIntegerArg(args[2]);

        if (quantityGiven < 1) {
            throw BadInputException("Bad input value for \"quantity\":\n"
                                    "\tGiven: " + args[2] + "\n" +
                                    "\tExpected: An integer value greater than 0.");
        }
        quantity = quantityGiven;
    }

    // We look for the first already existing stack of the same item in the user's inventory. If there is none, we
    // create a new stack and add it to the inventory.
    // Even if we throw an exception afterward, there won't be any problem since the inventory vector is not a pointer,
    // and is therefore not affected really until we set it at the end of the method.
    for (auto aStack: inventory) {
        if (aStack->top()->GetId() == itemId) {
            itemStack = aStack;
            break;
        }
    }
    if (itemStack == nullptr) {
        itemStack = new stack<Item*>();
        inventory.push_back(itemStack);
    }


    // Since it is not really efficient to open and search through the list of existing items or weapons or equipments,
    // we will simply retrieve it once, and copy it to multiple instances if the quantity is more than one.
    Item* item = GameLoader->GetItem(itemId);
    itemStack->push(item);

    for ( ; quantity > 1; quantity--) {
        itemStack->push(GetCopy(item));
    }

    Game->GetPlayer()->SetInventory(inventory);
}

Item *GiveCommand::GetCopy(Item *item) {
    Item *output;

    switch (item->GetRealType()) {
        case ItemType::ITEM:
            output = new Item(*item);
            break;
        case ItemType::WEAPON:
            output = new Weapon(*dynamic_cast<Weapon*>(item));
            break;
        case ItemType::EQUIPMENT:
            output = new Equipment(*dynamic_cast<Equipment*>(item));
            break;
    }

    return output;
}

GiveCommand::~GiveCommand() = default;
