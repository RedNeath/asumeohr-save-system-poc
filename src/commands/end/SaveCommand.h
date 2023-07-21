//
// Created by redneath on 21/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_SAVECOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_SAVECOMMAND_H


#include "../../interfaces/ICommand.h"

class SaveCommand: public ICommand {
public:
    explicit SaveCommand(class Game *Game);
    ~SaveCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_SAVECOMMAND_H
