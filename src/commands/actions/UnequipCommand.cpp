//
// Created by redneath on 22/07/23.
//

#include "UnequipCommand.h"
#include "../../exceptions/ImpossibleActionException.h"

using namespace std;

UnequipCommand::UnequipCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void UnequipCommand::Execute(std::vector<std::string> args) {
    if (args.size() > 1) {
        UnequipEquipment(args[1]);
    } else {
        UnequipWeapon();
    }
}

void UnequipCommand::UnequipWeapon() {
    Weapon *weapon = Game->GetPlayer()->GetWeapon();
    vector<stack<Item*>*> inventory = Game->GetPlayer()->GetInventory();
    stack<Item*> *itemStack = nullptr;

    if (weapon == nullptr) {
        throw ImpossibleActionException("There is no weapon equipped.");
    }

    // We look for the first already existing stack of the same item in the user's inventory. If there is none, we
    // create a new stack and add it to the inventory.
    // Even if we throw an exception afterward, there won't be any problem since the inventory vector is not a pointer,
    // and is therefore not affected really until we set it at the end of the method.
    for (auto aStack: inventory) {
        if (aStack->top()->GetId() == weapon->GetId()) {
            itemStack = aStack;
            break;
        }
    }
    if (itemStack == nullptr) {
        itemStack = new stack<Item*>();
        inventory.push_back(itemStack);
    }

    itemStack->push(weapon);
    Game->GetPlayer()->SetWeapon(nullptr);
    Game->GetPlayer()->SetInventory(inventory);
}

void UnequipCommand::UnequipEquipment(const string &argument) {
    int equipmentSlot = GetIntegerArg(argument) - 1;
    Equipment *equipment;
    vector<Equipment*> equipments = Game->GetPlayer()->GetEquipments();
    vector<stack<Item*>*> inventory = Game->GetPlayer()->GetInventory();
    stack<Item*> *itemStack = nullptr;

    if (equipments.empty()) {
        throw ImpossibleActionException("There is no equipment equipped.");
    }

    if (equipmentSlot < 0 || equipmentSlot > equipments.size() - 1) {
        throw BadInputException("Bad input value for \"equipment_slot\":\n"
                                "\tGiven: " + argument + "\n" +
                                "\tExpected: An integer value between 1 and " +
                                to_string(equipments.size()) + " (included).");
    }

    equipment = equipments[equipmentSlot];

    // We look for the first already existing stack of the same item in the user's inventory. If there is none, we
    // create a new stack and add it to the inventory.
    // Even if we throw an exception afterward, there won't be any problem since the inventory vector is not a pointer,
    // and is therefore not affected really until we set it at the end of the method.
    for (auto aStack: inventory) {
        if (aStack->top()->GetId() == equipment->GetId()) {
            itemStack = aStack;
            break;
        }
    }
    if (itemStack == nullptr) {
        itemStack = new stack<Item*>();
        inventory.push_back(itemStack);
    }

    itemStack->push(equipment);
    equipments.erase(equipments.begin() + equipmentSlot);
    Game->GetPlayer()->SetInventory(inventory);
    Game->GetPlayer()->SetEquipments(equipments);
}

UnequipCommand::~UnequipCommand() = default;
