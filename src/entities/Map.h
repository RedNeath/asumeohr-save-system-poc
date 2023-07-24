//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_MAP_H
#define ASUMEOHR_SAVE_SYSTEM_POC_MAP_H


#include <string>
#include <Magick++.h>
#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;
using namespace Magick;

class Map {
private:
    int Id;
    std::string IdentificationName;
    std::string Name;
    int Height;
    int Width;
    class Image Image;

public:
    Map(int id, const std::string &identificationName, const std::string &name, int height, int width);
    Map(const JsonDictionary &json, const std::string &identificationName);

    // Getters
    int GetId() const;
    const std::string &GetIdentificationName() const;
    const std::string &GetName() const;
    int GetHeight() const;
    int GetWidth() const;
    const class Image &getImage() const;

    // Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetHeight(int height);
    void SetWidth(int width);

    void setImage(const class Image &image);

    std::string ToString(const std::string &t);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_MAP_H
