//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_EQUIPCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_EQUIPCOMMAND_H


#include "../../Game.h"

class EquipCommand: public ICommand {
public:
    explicit EquipCommand(class Game *Game);
    ~EquipCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_EQUIPCOMMAND_H
