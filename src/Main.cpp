//
// Created by redneath on 14/07/23.
//
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << R"(Missing argument for selecting the implementation ["json" || "sqlite"])";
        return 134; // Failed assertion
    }

    // Converting the argument into a string
    string implementation = argv[1];

    if (implementation == "json") {
        // TODO
    } else if (implementation == "sqlite") {
        // TODO
    } else {
        cout << R"(The argument for the implementation must be one of ["json" || "sqlite"])";
        return 134; // Failed assertion
    }

    // Now that we have created an instance for the interface, we may load all the data.
    // TODO


    // And now it's time to display everything.
    // TODO


    // Finally, we free the memory and exit the program.
    // TODO

    return 0;
}
