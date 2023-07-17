//
// Created by redneath on 14/07/23.
//

#include "Player.h"
#include "../JsonGameLoader.h"

using namespace std;

Player::Player(int id, const std::string &name, class Map* map, int posX, int posY, class Weapon* weapon,
               const std::list<Equipment> &equipments, const std::list<std::stack<Item>> &inventory,
               const std::list<Skill> &skills) {
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
    Weapon = gameLoader->LoadWeapon(weapon);
    Equipments = gameLoader->LoadEquipments(equipments);
    Inventory = gameLoader->LoadInventory(inventory);
    Skills = gameLoader->LoadSkills(skills);
}

Player::~Player() {
    delete Map;
    delete Weapon;
}

void Player::to_json(JsonDictionary &json, const Player &player) {

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

const list<Equipment> &Player::GetEquipments() const {
    return Equipments;
}

const list<stack<Item>> &Player::GetInventory() const {
    return Inventory;
}

const list<Skill> &Player::GetSkills() const {
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

void Player::SetEquipments(const list<Equipment> &equipments) {
    Equipments = equipments;
}

void Player::SetInventory(const list<std::stack<Item>> &inventory) {
    Inventory = inventory;
}

void Player::SetSkills(const list<Skill> &skills) {
    Skills = skills;
}

void Player::SetMap(class Map *map) {
    Map = map;
}

void Player::SetWeapon(class Weapon *weapon) {
    Weapon = weapon;
}
