//
// Created by redneath on 14/07/23.
//

#include <iostream>
#include "Skill.h"
#include "../JsonGameLoader.h"

using namespace std;

Skill::Skill(int id, const string &name, const string &description) {
    Id = id;
    Name = name;
    Description = description;
}

Skill::Skill(const JsonDictionary &json) {
    json.at("id").get_to(Id);
    json.at("name").get_to(Name);
    json.at("description").get_to(Description);

    // Loading the icon
    string img_path;
    json.at("icon").get_to(img_path);
    img_path = JsonGameLoader::ASSETS_ICONS_DIR + img_path;

    Icon.read(img_path);
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

const Image &Skill::GetIcon() const {
    return Icon;
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

void Skill::SetIcon(const Image &icon) {
    Icon = icon;
}

string Skill::ToString(const string &t) {
    string output;

    output  = t + "SkillId:     " + to_string(Id) + "\n";
    output += t + "Name:        " + Name + "\n";
    output += t + "Description: " + Description;

    // Icon display
    cout << "Displaying icon for... \e[1m" << Name << "\e[0m" << endl;
    Icon.display();

    return output;
}
