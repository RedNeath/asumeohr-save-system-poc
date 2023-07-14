//
// Created by redneath on 14/07/23.
//

#include "Equipment.h"

#include <utility>

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

bool Equipment::Use() {
    // Place specific usage code here
    return true;
}
