//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H


#include <string>
#include <Magick++.h>
#include "nlohmann/json.hpp"
#include "../enums/ItemType.h"

using JsonDictionary = nlohmann::json;
using namespace Magick;

class Item {
protected:
    int Id;
    std::string Name;
    std::string Description;
    Image Icon;

public:
    Item(int id, const std::string &name, const std::string &description);
    Item(int id, const std::string &name, const std::string &description, std::vector<char> icon);
    explicit Item(const JsonDictionary &json);
    Item(const Item &item); // Copy constructor

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    const std::string &GetDescription() const;
    const Image &GetIcon() const;

    // Setters
    void SetName(const std::string &name);
    void SetDescription(const std::string &description);
    void SetIcon(const Image &icon);

    virtual std::string ToString(const std::string &t);
    virtual ItemType GetRealType();
    virtual JsonDictionary GetAsJsonInventory();
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H
