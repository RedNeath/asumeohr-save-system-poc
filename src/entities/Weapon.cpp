//
// Created by redneath on 14/07/23.
//

#include "Weapon.h"

using namespace std;

Weapon::Weapon(int id, const string &name, const string &description, float damage, float frequency,
               float loadTime, int range, int durability)
: Item(id, name, description) {
    Damage = damage;
    Frequency = frequency;
    LoadTime = loadTime;
    Range = range;
    Durability = durability;

    DurabilityLeft = durability;
}

Weapon::Weapon(int id, const string &name, const string &description, float damage, float frequency,
               float loadTime, int range, int durability, int durabilityLeft)
: Item(id, name, description) {
    Damage = damage;
    Frequency = frequency;
    LoadTime = loadTime;
    Range = range;
    Durability = durability;

    DurabilityLeft = durabilityLeft;
}

bool Weapon::Use() {
    // Place specific usage code here
    return false;
}

float Weapon::GetDamage() const {
    return Damage;
}

float Weapon::GetFrequency() const {
    return Frequency;
}

float Weapon::GetLoadTime() const {
    return LoadTime;
}

int Weapon::GetRange() const {
    return Range;
}

int Weapon::GetDurability() const {
    return Durability;
}

int Weapon::GetDurabilityLeft() const {
    return DurabilityLeft;
}

void Weapon::SetDamage(float damage) {
    Damage = damage;
}

void Weapon::SetFrequency(float frequency) {
    Frequency = frequency;
}

void Weapon::SetLoadTime(float loadTime) {
    LoadTime = loadTime;
}

void Weapon::SetRange(int range) {
    Range = range;
}

void Weapon::SetDurability(int durability) {
    Durability = durability;

    // Can't have more durability left than the total durability!
    if (durability < DurabilityLeft) {
        DurabilityLeft = durability;
    }
}
