//
// Created by redneath on 22/07/23.
//

#include "ForgetCommand.h"
#include "../../exceptions/NoMatchingSignature.h"

using namespace std;

ForgetCommand::ForgetCommand(class Game *Game) : ICommand(Game) {

}

void ForgetCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tforget <skill_slot:int>\n" +
                                  "For more information, see the README.md file.");
    }

    int slot = GetIntegerArg(args[1]) - 1;
    vector<Skill*> skills = Game->GetPlayer()->GetSkills();

    // Checking the skill slot
    if (slot < 0 || slot > skills.size() - 1) {
        throw BadInputException("Bad input value for \"skill_slot\":\n"
                                "\tGiven: " + args[1] + "\n"
                                "\tExpected: An integer value between 1 and " +
                                to_string(skills.size()) + ".");
    }

    Skill *skill = skills[slot];
    skills.erase(skills.begin() + slot);
    delete skill;
    Game->GetPlayer()->SetSkills(skills);
}

ForgetCommand::~ForgetCommand() = default;
