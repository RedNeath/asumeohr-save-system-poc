//
// Created by redneath on 14/07/23.
//

#include "Skill.h"

using namespace std;

Skill::Skill(int id, const string &name, const string &description) {
    Id = id;
    Name = name;
    Description = description;
}

int Skill::GetId() const {
    return Id;
}

const string &Skill::GetName() const {
    return Name;
}

const string &Skill::GetDescription() const {
    return Description;
}

void Skill::SetId(int id) {
    Id = id;
}

void Skill::SetName(const string &name) {
    Name = name;
}

void Skill::SetDescription(const string &description) {
    Description = description;
}
