//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_MAP_H
#define ASUMEOHR_SAVE_SYSTEM_POC_MAP_H


#include <string>
#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;

class Map {
private:
    int Id;
    std::string Name;
    int Height;
    int Width;
    // We'll see about the blobs later...

public:
    Map(int id, const std::string &name, int height, int width);
    Map(const JsonDictionary &json);

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    int GetHeight() const;
    int GetWidth() const;

    // Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetHeight(int height);
    void SetWidth(int width);

    std::string ToString(const std::string &t);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_MAP_H
