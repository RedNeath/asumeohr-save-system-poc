//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_UNEQUIPCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_UNEQUIPCOMMAND_H


#include "../../Game.h"

class UnequipCommand: public ICommand {

public:
    explicit UnequipCommand(class Game *Game, IGameLoader *gameLoader);
    ~UnequipCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_UNEQUIPCOMMAND_H
