//
// Created by redneath on 22/07/23.
//

#include "ProgressCommand.h"
#include "../../exceptions/NoMatchingSignature.h"

using namespace std;

ProgressCommand::ProgressCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void ProgressCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 3) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tprogress <variable_name:string> <state:int>\n" +
                                  "For more information, see the README.md file.");
    }

    State *variable = Game->GetState(args[1]);
    int state = GetIntegerArg(args[2]);

    // Checking that the variable given exists
    if (variable == nullptr) {
        throw BadInputException("Bad input value for \"variable_name\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: One of\n" + Game->GetStatesMapToString("\t\t"));
    }

    // Checking the given state
    if (state < 0 || state > 2) {
        throw BadInputException("Bad input value for \"state\":\n"
                                "\tGiven: " + args[2] + "\n" +
                                "\tExpected: An integer value between 0 and 2 included.");
    }


    // Affecting the variable
    *variable = static_cast<State>(state); // No display in this case.
}

ProgressCommand::~ProgressCommand() = default;
