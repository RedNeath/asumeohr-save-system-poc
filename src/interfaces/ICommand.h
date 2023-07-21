//
// Created by redneath on 21/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H

#include "../Game.h"

class ICommand {
protected:
    class Game *Game;

public:
    explicit ICommand(class Game *game) {
        Game = game;
    }
    virtual ~ICommand() = default;

    /**
     * By convention (according to what is done in the C++ main), the args will also contain the command name, even
     * though it is going to be useless and ignored most of the time.
     *
     * @param args The command args.
     */
    virtual void Execute(std::vector<std::string> args) = 0;
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H