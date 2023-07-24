//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_TELEPORTCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_TELEPORTCOMMAND_H


#include "../../Game.h"

class TeleportCommand: public ICommand {

public:
    explicit TeleportCommand(class Game *Game, IGameLoader *gameLoader);
    ~TeleportCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_TELEPORTCOMMAND_H
