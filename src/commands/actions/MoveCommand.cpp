//
// Created by redneath on 22/07/23.
//

#include "MoveCommand.h"
#include "../../exceptions/NoMatchingSignature.h"
#include "../../exceptions/DirectionNotFoundException.h"
#include "../../exceptions/ImpossibleActionException.h"

using namespace std;

MoveCommand::MoveCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void MoveCommand::Execute(vector<string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tmove <direction:string> [amount:int|\"max\"]\n" +
                                  "For more information, see the README.md file.");
    }

    // Getting and checking the direction
    Direction direction;
    auto directionPair = Directions.find(args[1]);
    if (directionPair == Directions.end()) {
        throw DirectionNotFoundException("No such direction: \"" + args[1] + "\".");
    }
    direction = directionPair->second;

    int amount;
    int target;
    int position;

    switch (direction) {
        case Direction::UP:
            target = 0;
            position = Game->GetPlayer()->GetPosY();

            amount = GetAmount(args, position, target);
            Game->GetPlayer()->SetPosY(position - amount);
            break;
        case Direction::RIGHT:
            target = Game->GetPlayer()->GetMap()->GetWidth() - 1;
            position = Game->GetPlayer()->GetPosX();

            amount = GetAmount(args, position, target);
            Game->GetPlayer()->SetPosX(position + amount);
            break;
        case Direction::DOWN:
            target = Game->GetPlayer()->GetMap()->GetHeight() - 1;
            position = Game->GetPlayer()->GetPosY();

            amount = GetAmount(args, position, target);
            Game->GetPlayer()->SetPosY(position + amount);
            break;
        case Direction::LEFT:
            target = 0;
            position = Game->GetPlayer()->GetPosX();

            amount = GetAmount(args, position, target);
            Game->GetPlayer()->SetPosX(position - amount);
            break;
    }
}

int MoveCommand::GetAmount(std::vector<std::string> args, int position, int target) {
    int amount = 1;
    int max;

    if (target < position) {
        max = position;
    } else {
        max = target - position;
    }

    if (max == 0) {
        throw ImpossibleActionException("Cannot move in that direction.");
    }

    if (args.size() >= 3 && args[2] == "max") {
        amount = max;
    } else if (args.size() >= 3) {
        int amountGiven = GetIntegerArg(args[2]);

        if (amountGiven < 1 || amountGiven > max) {
            throw BadInputException("Bad input value for \"amount\":\n"
                                    "\tGiven: " + args[2] + "\n" +
                                    "\tExpected: An integer value between 1 and " +
                                    to_string(max) + ".");
        }
        amount = amountGiven;
    }

    return amount;
}

MoveCommand::~MoveCommand() = default;
