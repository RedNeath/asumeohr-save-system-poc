//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_PROGRESSCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_PROGRESSCOMMAND_H


#include "../../Game.h"

class ProgressCommand: public ICommand {

public:
    explicit ProgressCommand(class Game *Game, IGameLoader *gameLoader);
    ~ProgressCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_PROGRESSCOMMAND_H
