//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_LEARNCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_LEARNCOMMAND_H


#include "../../Game.h"

class LearnCommand: public ICommand {

public:
    explicit LearnCommand(class Game *Game);
    ~LearnCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_LEARNCOMMAND_H
