//
// Created by redneath on 14/07/23.
//

#include "Map.h"

using namespace std;

Map::Map(int id, const string &name, int height, int width) {
    Id = id;
    Name = name;
    Height = height;
    Width = width;
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
