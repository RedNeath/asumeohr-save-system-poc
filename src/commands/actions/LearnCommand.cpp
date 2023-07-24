//
// Created by redneath on 22/07/23.
//

#include "LearnCommand.h"
#include "../../exceptions/NoMatchingSignature.h"
#include "../../exceptions/ImpossibleActionException.h"
#include "../../IGameLoader.h"

using namespace std;

LearnCommand::LearnCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void LearnCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 2) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tlearn <skill_id:int>\n" +
                                  "For more information, see the README.md file.");
    }

    int skillId = GetIntegerArg(args[1]);
    vector<Skill*> playerSkills = Game->GetPlayer()->GetSkills();

    // Checking the skill id is correct
    if (skillId < 4000 || skillId > 4999) {
        throw BadInputException("Bad input value for \"skill_id\":\n"
                                "\tGiven: " + args[1] + "\n" +
                                "\tExpected: An integer value between 4000 and 4999 (included).");
    }

    for (auto skill: playerSkills) {
        if (skill->GetId() == skillId) {
            throw ImpossibleActionException("You already learnt that skill earlier.");
        }
    }

    Skill *skill = GameLoader->GetSkill(skillId);
    playerSkills.push_back(skill);

    Game->GetPlayer()->SetSkills(playerSkills);
}

LearnCommand::~LearnCommand() = default;
