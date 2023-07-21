//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_FORGETCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_FORGETCOMMAND_H


#include "../../Game.h"

class ForgetCommand: public ICommand {

public:
    explicit ForgetCommand(class Game *Game);
    ~ForgetCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_FORGETCOMMAND_H
