//
// Created by redneath on 14/07/23.
//

#include <iostream>
#include "Map.h"
#include "../JsonGameLoader.h"

using namespace std;

Map::Map(int id, const string &name, int height, int width) {
    Id = id;
    Name = name;
    Height = height;
    Width = width;
}

Map::Map(const JsonDictionary &json, const string &mapName) {
    json.at("id").get_to(Id);
    json.at("name").get_to(Name);
    json.at("height").get_to(Height);
    json.at("width").get_to(Width);

    // Loading the map image
    string img_path = JsonGameLoader::MAPS_DIR + mapName + "/sprite.png";

    Image.read(img_path);
}

int Map::GetId() const {
    return Id;
}

const string &Map::GetName() const {
    return Name;
}

int Map::GetHeight() const {
    return Height;
}

int Map::GetWidth() const {
    return Width;
}

const Image &Map::getImage() const {
    return Image;
}

void Map::SetId(int id) {
    Id = id;
}

void Map::SetName(const string &name) {
    Name = name;
}

void Map::SetHeight(int height) {
    Height = height;
}

void Map::SetWidth(int width) {
    Width = width;
}

void Map::setImage(const class Image &image) {
    Image = image;
}

string Map::ToString(const string &t) {
    string output;

    output  = t + "MapId:   " + to_string(Id) + "\n";
    output += t + "Name:    " + Name + "\n";
    output += t + "Height:  " + to_string(Height) + "\n";
    output += t + "Width:   " + to_string(Width);

    // Image display
    cout << "Displaying map \e[1m" << Name << "\e[0m" << endl;
    Image.display();

    return output;
}
