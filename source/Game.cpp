#include "header/Game.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <json/json.h>

void Game::saveToFile(const std::string& filename) const {
    Json::Value jsonData;
    jsonData["name"] = name;
    jsonData["genre"] = genre;
    jsonData["version"] = std::to_underlying(version);
    jsonData["weight"] = weight;
    jsonData["cost"] = cost;

    std::ofstream out(filename);
    if (out.is_open()) {
        out << jsonData;
        out.close();
    } else {
        std::cerr << "Error opening file." << std::endl;
    }
}

Game Game::readFromFile(const std::string& filename) {
    Json::Value jsonData;
    std::ifstream in(filename);
    if (in.is_open()) {
        in >> jsonData;
        in.close();
    }

    std::string versionStr = jsonData["version"].asString();

    versions version;
    if (versionStr == "Pre_Alpha") {
        version = versions::Pre_Alpha;
    } else if (versionStr == "Alfa") {
        version = versions::Alfa;
    } else if (versionStr == "Beta") {
        version = versions::Beta;
    } else if (versionStr == "Release_Candidate") {
        version = versions::Release_Candidate;
    } else if (versionStr == "General_Availability") {
        version = versions::General_Availability;
    } else {
        throw std::runtime_error(versionStr + "Unknown version in file: ");
    }

    return {jsonData["name"].asString(),
            jsonData["genre"].asString(),
            version,
            jsonData["weight"].asFloat(),
            jsonData["cost"].asFloat()};
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
        case Release_Candidate:
            return "Release_Candidate";
        case General_Availability:
            return "General_Availability";
        default:
            return "Unknown";
    }
}

std::string Game::toString() const {
    return std::format("Name: {}, Genre: {}, Version: {}, Weight: {} Gb, Cost: ${}",
                       name, genre, versionToString(), weight, cost);
}