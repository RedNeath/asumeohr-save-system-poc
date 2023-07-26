//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENT_H
#define ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENT_H


#include "Item.h"
#include "../interfaces/ILimitedDurabilityItem.h"
#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;

class Equipment: public Item, protected ILimitedDurabilityItem {
private:
    float DamageAbsorption;
    int Durability;

public:
    Equipment(int id, const std::string &name, const std::string &description, float damageAbsorption, int durability);
    Equipment(int id, const std::string &name, const std::string &description, float damageAbsorption, int durability,
              int durabilityLeft);
    explicit Equipment(const JsonDictionary &json);
    Equipment(const Equipment &equipment); // Copy constructor

    bool Use() override;

    // Getters
    float GetDamageAbsorption() const;
    int GetDurability() const;
    int GetDurabilityLeft() const override;

    // Setters
    void SetDamageAbsorption(float damageAbsorption);
    void SetDurability(int durability);
    void SetDurabilityLeft(int durabilityLeft);

    std::string ToString(const std::string &t);
    ItemType GetRealType() override;
    JsonDictionary GetAsJson();
    JsonDictionary GetAsJsonInventory() override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_EQUIPMENT_H
