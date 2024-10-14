#include "header/Game.h"
#include <fstream>
#include <iostream>
#include <utility>

Game::Game(std::string n, std::string g, versions v, float w, float c)
    : name(std::move(n)), genre(std::move(g)), version(v), weight(w), cost(c) {}

void Game::saveToFile(std::ofstream& out) const {
    out << name << '\n' << genre << '\n' << std::to_underlying(version) << '\n'
        << weight << '\n' << cost << '\n';
}

Game Game::readFromFile(std::ifstream& in) {
    std::string n;
    std::string g;
    int v;
    float w;
    float c;

    getline(in, n);
    getline(in, g);
    in >> v >> w >> c;
    in.ignore();

    return {n, g, static_cast<versions>(v), w, c};
}

void Game::display() const {
    std::cout << toString() << std::endl;
}

void Game::updateVersion(versions newVersion) {
    version = newVersion;
}

std::string Game::getName() const {
    return name;
}

std::string Game::getGenre() const {
    return genre;
}

float Game::getWeight() const {
    return weight;
}

float Game::getCost() const {
    return cost;
}

std::string Game::versionToString() const {
    switch (version) {
        using enum versions;
        case Pre_Alpha:
            return "Pre_Alpha";
        case Alfa:
            return "Alfa";
        case Beta:
            return "Beta";
        case Release_candidate:
            return "Release_candidate";
        case General_availability:
            return "General_availability";
        default:
            return "Unknown";
    }
}

std::string Game::toString() const {
    return std::format("Name: {}, Genre: {}, Version: {}, Weight: {} Gb, Cost: ${}",
                       name, genre, versionToString(), weight, cost);
}

