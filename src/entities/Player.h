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

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H
#define ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H


class Player {
private:
    int Id;
    std::string Name;
    class Map *Map;
    int PosX;
    int PosY;
    class Weapon *Weapon;
    std::list<Equipment> Equipments;
    std::list<std::stack<Item>> Inventory; // Items may be stackable
    std::list<Skill> Skills;

public:
    Player(int id, const std::string &name, class Map *map, int posX, int posY, class Weapon *weapon,
           const std::list<Equipment> &equipments, const std::list<std::stack<Item>> &inventory,
           const std::list<Skill> &skills);
    ~Player();

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    int GetPosX() const;
    int GetPosY() const;
    const std::list<Equipment> &GetEquipments() const;
    const std::list<std::stack<Item>> &GetInventory() const;
    const std::list<Skill> &GetSkills() const;
    class Map *GetMap() const;
    class Weapon *GetWeapon() const;

    // Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetPosX(int posX);
    void SetPosY(int posY);
    void SetEquipments(const std::list<Equipment> &equipments);
    void SetInventory(const std::list<std::stack<Item>> &inventory);
    void SetSkills(const std::list<Skill> &skills);
    void SetMap(class Map *map);
    void SetWeapon(class Weapon *weapon);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_PLAYER_H
