//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DROPCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DROPCOMMAND_H


#include "../../Game.h"

class DropCommand: public ICommand {
public:
    explicit DropCommand(class Game *Game, IGameLoader *gameLoader);
    ~DropCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DROPCOMMAND_H
