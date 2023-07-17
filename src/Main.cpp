//
// Created by redneath on 14/07/23.
//
#include <iostream>
#include <string>
#include "IGameLoader.h"
#include "JsonGameLoader.h"
#include "SQLiteGameLoader.h"
#include "Game.h"

using namespace std;

int main(int argc, char *argv[]) {
    IGameLoader *gameLoader;
    if (argc < 3) {
        // For the v1, we won't allow the creation of a new save.
        cout << R"(Missing argument for selecting the implementation ["json" || "sqlite"] or the save name)";
        return 134; // Failed assertion
    }

    // Converting the argument into a string
    string implementation = argv[1];

    if (implementation == "json") {
        gameLoader = new JsonGameLoader();
    } else if (implementation == "sqlite") {
        gameLoader = new SQLiteGameLoader();
    } else {
        cout << R"(The argument for the implementation must be one of ["json" || "sqlite"])";
        return 134; // Failed assertion
    }

    // Now that we have created an instance for the interface, we may load all the data.
    GameSettings settings = GameSettings(); // Loading the settings there allows some overriding operations (for testing for example)
    settings.SaveName = argv[2];
    Game *game = gameLoader->LoadDataAndAssets(settings);


    // Theoretically, now we should loop on the Game Play method to let the user play.
    //while (true) {
    //    game.Play();
    //}

    // And now it's time to display everything.
    // TODO


    // Finally, we free the memory and exit the program.
    delete gameLoader;
    delete game;

    return 0;
}
