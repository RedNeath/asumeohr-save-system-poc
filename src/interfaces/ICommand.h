//
// Created by redneath on 21/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H

#include "../Game.h"

class IGameLoader;

class ICommand {
protected:
    class Game *Game;
    IGameLoader *GameLoader;

public:
    explicit ICommand(class Game *game, IGameLoader *gameLoader) {
        Game = game;
        GameLoader = gameLoader;
    }
    virtual ~ICommand() = default;

    /**
     * By convention (according to what is done in the C++ main), the args will also contain the command name, even
     * though it is going to be useless and ignored most of the time.
     *
     * @param args The command args.
     */
    virtual void Execute(std::vector<std::string> args) = 0;

    int GetIntegerArg(const std::string &arg) {
        int value;

        try {
            value = std::stoi(arg);
        } catch (std::invalid_argument &e) {
            value = -1;
        }

        return value;
    }
};

#endif //ASUMEOHR_SAVE_SYSTEM_POC_ICOMMAND_H
