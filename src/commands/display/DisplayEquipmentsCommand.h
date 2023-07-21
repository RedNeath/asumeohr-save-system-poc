//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYEQUIPMENTSCOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYEQUIPMENTSCOMMAND_H


#include "../../Game.h"

class DisplayEquipmentsCommand: public ICommand {

public:
    explicit DisplayEquipmentsCommand(class Game *Game);
    ~DisplayEquipmentsCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_DISPLAYEQUIPMENTSCOMMAND_H
