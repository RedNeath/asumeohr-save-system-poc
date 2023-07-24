//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYPLAYERCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYPLAYERCOMMAND_H


#include "../../Game.h"

class DisplayPlayerCommand: public ICommand {

public:
    explicit DisplayPlayerCommand(class Game *Game, IGameLoader *gameLoader);
    ~DisplayPlayerCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYPLAYERCOMMAND_H
