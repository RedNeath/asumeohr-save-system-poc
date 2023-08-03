//
// Created by redneath on 14/07/23.
//

#include <iostream>
#include "Item.h"
#include "../JsonGameLoader.h"

using namespace std;

Item::Item(int id, const string &name, const string &description) {
    Id = id;
    Name = name;
    Description = description;
}

Item::Item(int id, const string &name, const string &description, vector<char> icon) {
    Id = id;
    Name = name;
    Description = description;

    // Loading the image
    Blob blob(icon.data(), icon.size());
    Icon.read(blob);
}

Item::Item(const JsonDictionary &json) {
    json.at("id").get_to(Id);
    json.at("name").get_to(Name);
    json.at("description").get_to(Description);

    // Loading the icon
    string img_path;
    json.at("icon").get_to(img_path);
    img_path = JsonGameLoader::ASSETS_ICONS_DIR + img_path;

    Icon.read(img_path);
}

Item::Item(const Item &item) {
    Id = item.Id;
    Name = item.Name;
    Description = item.Description;
    Icon = item.Icon;
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

const Image &Item::GetIcon() const {
    return Icon;
}

void Item::SetName(const string &name) {
    Name = name;
}

void Item::SetDescription(const string &description) {
    Description = description;
}

void Item::SetIcon(const Image &icon) {
    Icon = icon;
}

string Item::ToString(const string &t) {
    string output;

    output  = t + "ItemId:      " + to_string(Id) + "\n";
    output += t + "Name:        " + Name + "\n";
    output += t + "Description: " + Description;

    // Icon display
    cout << "Displaying icon for... \e[1m" << Name << "\e[0m" << endl;
    Icon.display();

    return output;
}

ItemType Item::GetRealType() {
    return ItemType::ITEM;
}

JsonDictionary Item::GetAsJsonInventory() {
    JsonDictionary json = JsonDictionary();

    json["item"] = Id;

    return json;
}
