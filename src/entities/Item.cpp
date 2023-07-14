//
// Created by redneath on 14/07/23.
//

#include "Item.h"

#include <utility>

using namespace std;

Item::Item(int id, const string &name, const string &description) {
    Id = id;
    Name = name;
    Description = description;
}

int Item::GetId() const {
    return Id;
}

const string &Item::GetName() const {
    return Name;
}

const string &Item::GetDescription() const {
    return Description;
}

void Item::SetName(const string &name) {
    Name = name;
}

void Item::SetDescription(const string &description) {
    Description = description;
}
