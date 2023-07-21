//
// Created by redneath on 14/07/23.
//
#include <iostream>
#include <string>
#include <chrono>
#include "IGameLoader.h"
#include "JsonGameLoader.h"
#include "SQLiteGameLoader.h"
#include "Game.h"

using namespace std;

int main(int argc, char *argv[]) {
    IGameLoader *gameLoader;
    if (argc < 3) {
        // For the v1, we won't allow the creation of a new save.
        cout << R"(Missing argument for selecting the implementation ["json" || "sqlite"] or the save name)" << endl;
        return 134; // Failed assertion
    }

    // Converting the argument into a string
    string implementation = argv[1];

    // In a real implementation, this would ideally be done via dependency injection!
    if (implementation == "json") {
        gameLoader = new JsonGameLoader();
    } else if (implementation == "sqlite") {
        gameLoader = new SQLiteGameLoader();
    } else {
        cout << R"(The argument for the implementation must be one of ["json" || "sqlite"])" << endl;
        return 134; // Failed assertion
    }

    // Starting elapsed time calculation
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // Now that we have created an instance for the interface, we may load all the data.
    GameSettings settings = GameSettings(); // Loading the settings there allows some overriding operations (for testing for example)
    settings.SaveName = argv[2];
    Game *game = gameLoader->LoadDataAndAssets(settings);
    cout << "Successfully loaded all the necessary data and assets! ❤\uFE0F" << endl;

    // Stopping the elapsed time calculation
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // Now it's time to display everything.
    cout << endl << endl << game->ToString("") << endl;
    cout << "Loading time: " << (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) << "ms" << endl;


    // Now we loop on the game's Play method, to let the user use commands
    do {
        game->Play();
    } while (!game->HasEnded());


    // Finally, we free the memory and exit the program.
    delete gameLoader;
    delete game;

    return 0;
}
