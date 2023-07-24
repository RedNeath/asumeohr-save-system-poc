//
// Created by redneath on 22/07/23.
//

#ifndef ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H
#define ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H


#include "../../Game.h"
#include "../../enums/Direction.h"

class MoveCommand: public ICommand {
private:
    const std::unordered_map<std::string,Direction> Directions = {
            {"up", Direction::UP},
            {"right", Direction::RIGHT},
            {"down", Direction::DOWN},
            {"left", Direction::LEFT}
    };
    int GetAmount(std::vector<std::string> args, int position, int target);

public:
    explicit MoveCommand(class Game *Game, IGameLoader *gameLoader);
    ~MoveCommand() override;

    void Execute(std::vector<std::string> args) override;
};


#endif //ASUMEOHR_SAVE_SYSTEM_POC_MOVECOMMAND_H
