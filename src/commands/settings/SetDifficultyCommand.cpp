//
// Created by redneath on 22/07/23.
//

#include "SetDifficultyCommand.h"
#include "../../exceptions/NoMatchingSignature.h"


SetDifficultyCommand::SetDifficultyCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void SetDifficultyCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tset_difficulty <difficulty:int>\n" +
                                  "For more information, see the README.md file.");
    }

    int difficulty = GetIntegerArg(args[1]);

    // Checking the given difficulty
    if (difficulty < 0 || difficulty > 3) {
        throw BadInputException("Bad input value for \"difficulty\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: An integer value between 0 and 3 included.");
    }

    // Affecting the variable
    Game->Difficulty = static_cast<Difficulty>(difficulty); // Might not work...
}

SetDifficultyCommand::~SetDifficultyCommand() = default;
