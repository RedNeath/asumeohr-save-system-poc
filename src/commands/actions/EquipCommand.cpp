//
// Created by redneath on 22/07/23.
//

#include "EquipCommand.h"
#include "../../exceptions/NoMatchingSignature.h"
#include "../../exceptions/ImpossibleActionException.h"
#include "DropCommand.h"

using namespace std;

EquipCommand::EquipCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void EquipCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tequip <inventory_slot:int>\n" +
                                  "For more information, see the README.md file.");
    }

    int slot = GetIntegerArg(args[1]) - 1;
    vector<stack<Item*>*> inventory = Game->GetPlayer()->GetInventory();

    if (inventory.empty()) {
        throw ImpossibleActionException("There is nothing in the inventory.");
    }

    // Checking the inventory slot
    if (slot < 0 || slot > inventory.size() - 1 ||
        (inventory[slot]->top()->GetRealType() != ItemType::EQUIPMENT && inventory[slot]->top()->GetRealType() != ItemType::WEAPON))
    {
        throw BadInputException("Bad input value for \"inventory_slot\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: An integer value between 1 and " +
                                to_string(inventory.size()) + ", designating a weapon or an equipment.");
    }

    switch(inventory[slot]->top()->GetRealType()) {
        case ItemType::WEAPON:
            EquipWeapon(dynamic_cast<Weapon *>(inventory[slot]->top()));
            break;

        case ItemType::EQUIPMENT:
            EquipEquipment(dynamic_cast<Equipment *>(inventory[slot]->top()));
            break;
    }

    // Can't use the drop command, because it will delete the pointer...
    inventory[slot]->pop();
    if (inventory[slot]->empty()) {
        stack<Item*>* itemStack = inventory[slot];
        inventory.erase(inventory.begin() + slot);
        delete itemStack;
    }

    Game->GetPlayer()->SetInventory(inventory);
}

void EquipCommand::EquipWeapon(Weapon *weapon) {
    if (Game->GetPlayer()->GetWeapon() != nullptr) {
        throw ImpossibleActionException("There is already one weapon equipped.");
    }

    Game->GetPlayer()->SetWeapon(weapon);
}

void EquipCommand::EquipEquipment(Equipment *equipment) {
    vector<Equipment*> equipments = Game->GetPlayer()->GetEquipments();
    equipments.push_back(equipment);

    Game->GetPlayer()->SetEquipments(equipments);
}

EquipCommand::~EquipCommand() = default;
