//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_GIVECOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_GIVECOMMAND_H


#include "../../Game.h"

class GiveCommand: public ICommand {
public:
    explicit GiveCommand(class Game *Game, IGameLoader *gameLoader);
    ~GiveCommand() override;

    void Execute(std::vector<std::string> args) override;
    Item *GetCopy(Item *item);
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_GIVECOMMAND_H
