//
// Created by redneath on 14/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H


#include <string>

class Item {
protected:
    int Id;
    std::string Name;
    std::string Description;
    // We'll see for the blobs later

public:
    Item(int id, const std::string &name, const std::string &description);

    // Getters
    int GetId() const;
    const std::string &GetName() const;
    const std::string &GetDescription() const;

    // Setters
    void SetName(const std::string &name);
    void SetDescription(const std::string &description);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_ITEM_H