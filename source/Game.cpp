#include <iostream>
#include <fstream>
#include <string>
#include "header/Game.h"

using namespace std;

void Game::display() const {
    cout << "Name: " << name << endl;
    cout << "Genre: " << genre << endl;
    cout << "Version: " << versionToString() << endl;
    cout << "Weight: " << weight << "Gb" << endl;
    cout << "Cost: " << cost << "$" << endl;
    cout << "\n";
}

void Game::updateVersion(versions newVersion) {
    version = newVersion;
}

[[nodiscard]] string Game::getName() const {
    return name;
}

[[nodiscard]] float Game::getWeight() const {
    return weight;
}

[[nodiscard]] float Game::getCost() const {
    return cost;
}

[[nodiscard]] string Game::getGenre() const {
    return genre;
}

