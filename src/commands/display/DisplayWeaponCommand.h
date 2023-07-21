//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYWEAPONCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYWEAPONCOMMAND_H


#include "../../Game.h"

class DisplayWeaponCommand: public ICommand {

public:
    explicit DisplayWeaponCommand(class Game *Game);
    ~DisplayWeaponCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYWEAPONCOMMAND_H
