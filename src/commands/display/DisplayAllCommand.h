//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYALLCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYALLCOMMAND_H


#include "../../Game.h"

class DisplayAllCommand: public ICommand {

public:
    explicit DisplayAllCommand(class Game *Game, IGameLoader *gameLoader);
    ~DisplayAllCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYALLCOMMAND_H
