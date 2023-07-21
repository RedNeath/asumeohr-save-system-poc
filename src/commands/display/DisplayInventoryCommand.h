//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYINVENTORYCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYINVENTORYCOMMAND_H


#include "../../Game.h"

class DisplayInventoryCommand: public ICommand {

public:
    explicit DisplayInventoryCommand(class Game *Game);
    ~DisplayInventoryCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYINVENTORYCOMMAND_H
