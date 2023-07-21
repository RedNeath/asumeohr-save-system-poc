//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_EXITCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_EXITCOMMAND_H


#include "../../Game.h"

class ExitCommand: public ICommand {
public:
    explicit ExitCommand(class Game *Game);
    ~ExitCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_EXITCOMMAND_H
