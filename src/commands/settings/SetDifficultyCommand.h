//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SETDIFFICULTYCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SETDIFFICULTYCOMMAND_H


#include "../../Game.h"

class SetDifficultyCommand: public ICommand {

public:
    explicit SetDifficultyCommand(class Game *Game, IGameLoader *gameLoader);
    ~SetDifficultyCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SETDIFFICULTYCOMMAND_H
