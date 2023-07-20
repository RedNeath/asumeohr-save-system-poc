//
// Created by redneath on 14/07/23.
//

#include "Equipment.h"

#include <utility>
#include <iostream>

using namespace std;

Equipment::Equipment(int id, const string &name, const string &description, float damageAbsorption, int durability)
: Item(id, name, description) {
    DamageAbsorption = damageAbsorption;
    Durability = durability;

    DurabilityLeft = durability;
}

Equipment::Equipment(int id, const string &name, const string &description, float damageAbsorption, int durability,
                     int durabilityLeft)
: Item(id, name, description) {
    DamageAbsorption = damageAbsorption;
    Durability = durability;

    DurabilityLeft = durabilityLeft;
}

Equipment::Equipment(const JsonDictionary &json) : Item(json) {
    json.at("damageAbsorption").get_to(DamageAbsorption);
    json.at("durability").get_to(Durability);
}

bool Equipment::Use() {
    // Place specific usage code here
    return true;
}

float Equipment::GetDamageAbsorption() const {
    return DamageAbsorption;
}

int Equipment::GetDurability() const {
    return Durability;
}

int Equipment::GetDurabilityLeft() const {
    return DurabilityLeft;
}

void Equipment::SetDamageAbsorption(float damageAbsorption) {
    DamageAbsorption = damageAbsorption;
}

void Equipment::SetDurability(int durability) {
    Durability = durability;

    // Can't have more durability left than the total durability!
    if (durability < DurabilityLeft) {
        DurabilityLeft = durability;
    }
}

void Equipment::SetDurabilityLeft(int durabilityLeft) {
    DurabilityLeft = durabilityLeft;
}

string Equipment::ToString(const string &t) {
    string output;

    output  = t + "EquipmentId:         " + to_string(Id) + "\n";
    output += t + "Name:                " + Name + "\n";
    output += t + "Description:         " + Description + "\n";
    output += t + "DamageAbsorption:    " + to_string(DamageAbsorption) + "\n";
    output += t + "Durability:          " + to_string(Durability) + "\n";
    output += t + "DurabilityLeft:      " + to_string(DurabilityLeft);

    // Icon display
    cout << "Displaying icon for... \e[1m" << Name << "\e[0m" << endl;
    Icon.display();

    return output;
}
