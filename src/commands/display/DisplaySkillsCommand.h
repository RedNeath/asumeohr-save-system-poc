//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYSKILLSCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYSKILLSCOMMAND_H


#include "../../Game.h"

class DisplaySkillsCommand: public ICommand {

public:
    explicit DisplaySkillsCommand(class Game *Game, IGameLoader *gameLoader);
    ~DisplaySkillsCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYSKILLSCOMMAND_H
