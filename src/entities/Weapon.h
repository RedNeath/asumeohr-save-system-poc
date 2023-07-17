//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_WEAPON_H
#define ASUMEOHR_SAVE_SYSTEM_POC_WEAPON_H


#include "Item.h"
#include "../interfaces/ILimitedDurabilityItem.h"

class Weapon: public Item, protected ILimitedDurabilityItem {
private:
    float Damage;
    float Frequency;
    float LoadTime;
    int Range;
    int Durability;

public:
    Weapon(int id, const std::string &name, const std::string &description, float damage, float frequency,
           float loadTime, int range, int durability);
    Weapon(int id, const std::string &name, const std::string &description, float damage, float frequency,
           float loadTime, int range, int durability, int durabilityLeft);

    bool Use() override;

    // Getters
    float GetDamage() const;
    float GetFrequency() const;
    float GetLoadTime() const;
    int GetRange() const;
    int GetDurability() const;
    int GetDurabilityLeft() const;

    // Setters
    void SetDamage(float damage);
    void SetFrequency(float frequency);
    void SetLoadTime(float loadTime);
    void SetRange(int range);
    void SetDurability(int durability);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_WEAPON_H
