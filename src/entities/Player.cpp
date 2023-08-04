//
// Created by redneath on 14/07/23.
//

#include "Player.h"
#include "../JsonGameLoader.h"

using namespace std;

Player::Player(int id, const std::string &name, class Map* map, int posX, int posY, class Weapon* weapon,
               const std::vector<Equipment*> &equipments, const std::vector<std::stack<Item*>*> &inventory,
               const std::vector<Skill*> &skills) {
    Id = id;
    Name = name;
    Map = map;
    PosX = posX;
    PosY = posY;
    Weapon = weapon;
    Equipments = equipments;
    Inventory = inventory;
    Skills = skills;
}

Player::Player(JsonGameLoader *gameLoader, const JsonDictionary &metadata, const JsonDictionary &equipments,
               const JsonDictionary &inventory, const JsonDictionary &skills) {
    string mapName;
    JsonDictionary weapon;

    metadata.at("id").get_to(Id);
    metadata.at("name").get_to(Name);
    metadata.at("map").get_to(mapName);
    metadata.at("posX").get_to(PosX);
    metadata.at("posY").get_to(PosY);
    metadata.at("weapon").get_to(weapon);

    Map = gameLoader->LoadMap(mapName);
    Equipments = gameLoader->LoadEquipments(equipments);
    Inventory = gameLoader->LoadInventory(inventory);
    Skills = gameLoader->LoadSkills(skills);

    try {
        Weapon = gameLoader->LoadWeapon(weapon);
    } catch (nlohmann::json_abi_v3_11_2::detail::type_error &e) {
        Weapon = nullptr;
    }
}

Player::~Player() {
    // delete Map; // Mustn't be done, it will be freed in the cache, as they share references.
    delete Weapon;

    for (int i = (int) Equipments.size() - 1; i >= 0; i--) {
        delete Equipments[i];
    }

    for (int i = (int) Skills.size() - 1; i >= 0; i--) {
        delete Skills[i];
    }

    for (int i = (int) Inventory.size() - 1; i >= 0; i--) {
        Item* val;
        while (!Inventory[i]->empty()) {
            val = Inventory[i]->top();
            Inventory[i]->pop();

            delete val;
        }
        delete Inventory[i];
    }
}

int Player::GetId() const {
    return Id;
}

const string &Player::GetName() const {
    return Name;
}

int Player::GetPosX() const {
    return PosX;
}

int Player::GetPosY() const {
    return PosY;
}

const vector<Equipment*> &Player::GetEquipments() const {
    return Equipments;
}

const vector<stack<Item*>*> &Player::GetInventory() const {
    return Inventory;
}

const vector<Skill*> &Player::GetSkills() const {
    return Skills;
}

Map *Player::GetMap() const {
    return Map;
}

Weapon *Player::GetWeapon() const {
    return Weapon;
}

void Player::SetId(int id) {
    Id = id;
}

void Player::SetName(const string &name) {
    Name = name;
}

void Player::SetPosX(int posX) {
    PosX = posX;
}

void Player::SetPosY(int posY) {
    PosY = posY;
}

void Player::SetEquipments(const vector<Equipment*> &equipments) {
    Equipments = equipments;
}

void Player::SetInventory(const vector<std::stack<Item*>*> &inventory) {
    Inventory = inventory;
}

void Player::SetSkills(const vector<Skill*> &skills) {
    Skills = skills;
}

void Player::SetMap(class Map *map) {
    Map = map;
}

void Player::SetWeapon(class Weapon *weapon) {
    Weapon = weapon;
}

string Player::ToString(const string &t) {
    string output;
    int index;

    output  = t + "PlayerId:    " + to_string(Id) + "\n";
    output += t + "Name:        " + Name + "\n";
    output += t + "Map:\n"        + Map->ToString(t + "\t") + "\n";
    output += t + "PosX:        " + to_string(PosX) + "\n";
    output += t + "PosY:        " + to_string(PosY) + "\n";
    output += t + "Weapon:\n";
    if (Weapon == nullptr) {
        output += t + "\tNo weapon equipped";
    } else {
        output += Weapon->ToString(t + "\t");
    }
    output += "\n";

    output += t + "Equipments:\n"; // + Weapon->ToString(t + "\t") + "\n";
    index = 1;
    for (Equipment *equipment: Equipments) {
        output += t + "\tEquipment " + to_string(index) + ":\n";
        output += equipment->ToString(t + "\t\t") + "\n";
        index++;
    }

    output += t + "Skills:\n";
    index = 1;
    for (Skill *skill: Skills) {
        output += t + "\tSkill " + to_string(index) + ":\n";
        output += skill->ToString(t + "\t\t") + "\n";
        index++;
    }

    output += t + "Inventory:\n";
    index = 1;
    for (stack<Item*> *itemStack: Inventory) {
        output += t + "\tItem stack " + to_string(index) + ":\n";
        output += itemStack->top()->ToString(t + "\t\t") + "\n";
        output += t + "\t\tQuantity: " + to_string(itemStack->size()) + "\n";
        index++;
    }

    return output;
}

JsonDictionary Player::GetEquipmentsAsJson() {
    JsonDictionary json = JsonDictionary::array();

    for (auto equipment: Equipments) {
        json.push_back(equipment->GetAsJson());
    }

    return json;
}

JsonDictionary Player::GetInventoryAsJson() {
    JsonDictionary json = JsonDictionary::array();
    vector<unordered_map<string, int>> jsonInventory = vector<unordered_map<string, int>>();

    for (auto itemStack: Inventory) {
        JsonDictionary elem = itemStack->top()->GetAsJsonInventory();

        // We just need to add the stack size
        elem["quantity"] = itemStack->size();

        json.push_back(elem);
    }

    return json;
}

JsonDictionary Player::GetMetadataAsJson() {
    JsonDictionary json = JsonDictionary();

    json["id"] = Id;
    json["name"] = Name;
    json["map"] = Map->GetIdentificationName();
    json["posX"] = PosX;
    json["posY"] = PosY;
    if (Weapon != nullptr) {
        json["weapon"] = Weapon->GetAsJson();
    } else {
        json["weapon"] = nullptr;
    }

    return json;
}

JsonDictionary Player::GetSkillsAsJson() {
    JsonDictionary json = JsonDictionary::array();

    for (auto skill: Skills) {
        json.push_back(skill->GetId());
    }

    return json;
}
