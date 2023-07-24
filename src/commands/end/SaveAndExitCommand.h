//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SAVEANDEXITCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SAVEANDEXITCOMMAND_H


#include "../../Game.h"

class SaveAndExitCommand: public ICommand {
public:
    explicit SaveAndExitCommand(class Game *Game, IGameLoader *gameLoader);
    ~SaveAndExitCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SAVEANDEXITCOMMAND_H
