//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCOMMAND_H


#include "../../Game.h"

class DisplayMapCommand: public ICommand {

public:
    explicit DisplayMapCommand(class Game *Game, IGameLoader *gameLoader);
    ~DisplayMapCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCOMMAND_H
