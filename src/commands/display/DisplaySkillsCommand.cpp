// Commands infrastructure (Command pattern)
// Created by redneath on 22/07/23.
//

#include <iostream>
#include "DisplaySkillsCommand.h"

using namespace std;

DisplaySkillsCommand::DisplaySkillsCommand(class Game *Game) : ICommand(Game) {

}

void DisplaySkillsCommand::Execute(std::vector<std::string> args) {
    vector<Skill*> playerSkills = Game->GetPlayer()->GetSkills();
    string output; // See DisplayEquipmentsCommand
    int index = 1;

    for (auto item: playerSkills) {
        output += "Skill " + to_string(index) + ":\n";
        output += item->ToString("\t") + "\n";

        index++;
    }

    cout << output;
}

DisplaySkillsCommand::~DisplaySkillsCommand() = default;
