//
// Created by redneath on 22/07/23.
//

#include "TeleportCommand.h"
#include "../../exceptions/NoMatchingSignature.h"
#include "../../IGameLoader.h"

using namespace std;

TeleportCommand::TeleportCommand(class Game *Game, IGameLoader *gameLoader) : ICommand(Game, gameLoader) {

}

void TeleportCommand::Execute(std::vector<std::string> args) {
    if (args.size() < 3) {
        throw NoMatchingSignature("The command \"" + args[0] + "\" needs more arguments than given.\n" +
                                  "Expected signature:\n" +
                                  "\tteleport [map_name:string] <pos_x:int> <pos_y:int>\n" +
                                  "For more information, see the README.md file.");
    }

    string mapName;
    int posX;
    int posY;
    Map *map;

    // Two options: we have 3 arguments, so the map remains the same, or we have 4 or more, so the map changes
    if (args.size() == 3) {
        posX = GetIntegerArg(args[1]);
        posY = GetIntegerArg(args[2]);

        map = Game->GetPlayer()->GetMap();
    } else { // If there is a map change, we will try to change it straightaway
        mapName = args[1];
        posX = GetIntegerArg(args[2]);
        posY = GetIntegerArg(args[3]);

        map = Game->GetMaps()->Get(mapName);
        if (map == nullptr) { // The map is not in the cache
            map = GameLoader->LoadMap(mapName);
            Game->GetMaps()->Put(mapName, map);
        }
    }

    // Now we only have to move to the given coordinates... if they are correct!
    if (posX < 0 || posX >= map->GetWidth() || posY < 0 || posY >= map->GetHeight()) {
        throw BadInputException("Bad coordinates for map \"" + map->GetName() + "\":\n" +
                                "\tGiven: X=" + to_string(posX) + "\n" +
                                "\t       Y=" + to_string(posY) + "\n" +
                                "\tExpected: X∈[0;" + to_string(map->GetWidth()-1) + "]\n"
                                "\t          Y∈[0;" + to_string(map->GetHeight()-1) + "]");
    }

    // Everything is correct, so we'll re-affect the map to the user and give them their new position
    Game->GetPlayer()->SetMap(map);
    Game->GetPlayer()->SetPosX(posX);
    Game->GetPlayer()->SetPosY(posY);
}

TeleportCommand::~TeleportCommand() = default;
