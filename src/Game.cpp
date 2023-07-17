//
// Created by redneath on 16/07/23.
//

#include "Game.h"

using namespace std;

Game::Game(class Player *player, HeavyResourcesCache<Map> *maps) {
    Player = player;
    Maps = maps;
}

Game::~Game() {
    delete Player;
    delete Maps;
}

void Game::Play() {
    // Will do nothing in our example.
}

Player *Game::GetPlayer() const {
    return Player;
}

HeavyResourcesCache<Map> *Game::GetMaps() const {
    return Maps;
}

void Game::SetPlayer(class Player *player) {
    Player = player;
}

void Game::SetMaps(HeavyResourcesCache<Map> *maps) {
    Maps = maps;
}

string Game::ToString(const string &t) {
    string output;

    output  = "Player data:\n";
    output +=  Player->ToString(t + "\t") + "\n";

    //TODO
    //output += "Maps cache data:\n";
    //output +=  Maps->ToString(t + "\t");

    return output;
}
