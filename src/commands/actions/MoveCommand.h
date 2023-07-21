//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H


#include "../../Game.h"

class MoveCommand: public ICommand {

public:
    explicit MoveCommand(class Game *Game);
    ~MoveCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H
