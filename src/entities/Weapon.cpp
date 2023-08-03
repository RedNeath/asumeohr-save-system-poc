//
// Created by redneath on 14/07/23.
//

#include <iostream>
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

Weapon::Weapon(int id, const string &name, const string &description, vector<char> icon, float damage, float frequency,
               float loadTime, int range, int durability, int durabilityLeft)
: Item(id, name, description, icon) {
    Damage = damage;
    Frequency = frequency;
    LoadTime = loadTime;
    Range = range;
    Durability = durability;

    DurabilityLeft = durabilityLeft;
}

Weapon::Weapon(const JsonDictionary &json) : Item(json) {
    json.at("damage").get_to(Damage);
    json.at("frequency").get_to(Frequency);
    json.at("loadTime").get_to(LoadTime);
    json.at("range").get_to(Range);
    json.at("durability").get_to(Durability);
}

Weapon::Weapon(const Weapon &weapon) : Item(weapon) {
    Damage = weapon.Damage;
    Frequency = weapon.Frequency;
    LoadTime = weapon.LoadTime;
    Range = weapon.Range;
    Durability = weapon.Durability;

    DurabilityLeft = weapon.DurabilityLeft;
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

void Weapon::SetDurabilityLeft(int durabilityLeft) {
    DurabilityLeft = durabilityLeft;
}

string Weapon::ToString(const string &t) {
    string output;

    output  = t + "WeaponId:        " + to_string(Id) + "\n";
    output += t + "Name:            " + Name + "\n";
    output += t + "Description:     " + Description + "\n";
    output += t + "Damage:          " + to_string(Damage) + "\n";
    output += t + "Frequency:       " + to_string(Frequency) + "\n";
    output += t + "LoadTime:        " + to_string(LoadTime) + "\n";
    output += t + "Range:           " + to_string(Range) + "\n";
    output += t + "Durability:      " + to_string(Durability) + "\n";
    output += t + "DurabilityLeft:  " + to_string(DurabilityLeft);

    // Icon display
    cout << "Displaying icon for... \e[1m" << Name << "\e[0m" << endl;
    Icon.display();

    return output;
}

ItemType Weapon::GetRealType() {
    return ItemType::WEAPON;
}

JsonDictionary Weapon::GetAsJson() {
    JsonDictionary json = JsonDictionary();

    json["id"] = Id;
    json["durabilityLeft"] = DurabilityLeft;

    return json;
}

JsonDictionary Weapon::GetAsJsonInventory() {
    JsonDictionary json = JsonDictionary();

    json["item"] = Id;
    json["durabilityLeft"] = DurabilityLeft;

    return json;
}
