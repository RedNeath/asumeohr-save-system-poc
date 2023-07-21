//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCACHECOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCACHECOMMAND_H


#include "../../Game.h"

class DisplayMapCacheCommand: public ICommand {

public:
    explicit DisplayMapCacheCommand(class Game *Game);
    ~DisplayMapCacheCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYMAPCACHECOMMAND_H
