//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_TOGGLECHOSECLASSCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_TOGGLECHOSECLASSCOMMAND_H


#include "../../Game.h"

class ToggleChoseClassCommand: public ICommand {

public:
    explicit ToggleChoseClassCommand(class Game *Game, IGameLoader *gameLoader);
    ~ToggleChoseClassCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_TOGGLECHOSECLASSCOMMAND_H
