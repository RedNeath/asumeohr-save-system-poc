//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H


#include <string>
#include <Magick++.h>
#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;
using namespace Magick;

class Skill {
private:
    int Id;
    std::string Name;
    std::string Description;
    Image Icon;
    // We'll see for the blobs later...

public:
    Skill(int id, const std::string &name, const std::string &description);
    Skill(const JsonDictionary &json);

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    const std::string &GetDescription() const;
    const Image &GetIcon() const;

    //Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetDescription(const std::string &description);
    void SetIcon(const Image &icon);

    std::string ToString(const std::string &t);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H
