//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H


#include <string>
#include "nlohmann/json.hpp"

using JsonDictionary = nlohmann::json;

class Skill {
private:
    int Id;
    std::string Name;
    std::string Description;
    // We'll see for the blobs later...

public:
    Skill(int id, const std::string &name, const std::string &description);
    Skill(const JsonDictionary &json);

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    const std::string &GetDescription() const;

    //Setters
    void SetId(int id);
    void SetName(const std::string &name);
    void SetDescription(const std::string &description);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SKILL_H
