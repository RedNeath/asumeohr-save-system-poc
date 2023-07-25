//
// Created by redneath on 14/07/23.
//
#include <string>
#include <list>
#include <stack>
#include "Map.h"
#include "Equipment.h"
#include "Item.h"
#include "Weapon.h"
#include "Skill.h"
#include "nlohmann/json.hpp"

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H

using JsonDictionary = nlohmann::json;

class JsonGameLoader;

class Player {
private:
    int Id;
    std::string Name;
    class Map *Map;
    int PosX;
    int PosY;
    class Weapon *Weapon;
    std::vector<Equipment*> Equipments;
    std::vector<std::stack<Item*>*> Inventory; // Items may be stackable
    std::vector<Skill*> Skills;

public:
    Player(int id, const std::string &name, class Map *map, int posX, int posY, class Weapon *weapon,
           const std::vector<Equipment*> &equipments, const std::vector<std::stack<Item*>*> &inventory,
           const std::vector<Skill*> &skills);
    Player(JsonGameLoader *gameLoader, const JsonDictionary &metadata, const JsonDictionary &equipments,
           const JsonDictionary &inventory, const JsonDictionary &skills);
    ~Player();

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    int GetPosX() const;
    int GetPosY() const;
    const std::vector<Equipment*> &GetEquipments() const;
    const std::vector<std::stack<Item*>*> &GetInventory() const;
    const std::vector<Skill*> &GetSkills() const;
    class Map *GetMap() const;
    class Weapon *GetWeapon() const;

    // Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetPosX(int posX);
    void SetPosY(int posY);
    void SetEquipments(const std::vector<Equipment*> &equipments);
    void SetInventory(const std::vector<std::stack<Item*>*> &inventory);
    void SetSkills(const std::vector<Skill*> &skills);
    void SetMap(class Map *map);
    void SetWeapon(class Weapon *weapon);

    std::string ToString(const std::string &t);
    JsonDictionary GetEquipmentsAsJson();
    JsonDictionary GetInventoryAsJson();
    JsonDictionary GetMetadataAsJson();
    JsonDictionary GetSkillsAsJson();
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H
