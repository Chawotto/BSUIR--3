#include "header/Game.h"
#include <fstream>
#include <utility>
#include <json/json.h>

class GameException : public std::exception {
private:
    std::string message;

public:
    explicit GameException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

void Game::saveToFile(const std::string& filename) const {
    Json::Value jsonData;
    jsonData["name"] = name;
    jsonData["genre"] = genre;
    jsonData["version"] = std::to_underlying(version);
    jsonData["weight"] = weight;
    jsonData["cost"] = cost;

    std::ofstream out(filename);
    if (!out.is_open()) {
        throw GameException("Error opening file: " + filename);
    }

    out << jsonData;
}

Game Game::readFromFile(const std::string& filename) {
    Json::Value jsonData;
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw GameException("Error opening file: " + filename);
    }

    in >> jsonData;

    if (!jsonData.isMember("version")) {
        throw GameException("Version is missing in the JSON data.");
    }

    auto version = static_cast<versions>(jsonData["version"].asInt());

    return {
        jsonData["name"].asString(),
        jsonData["genre"].asString(),
        version,
        jsonData["weight"].asFloat(),
        jsonData["cost"].asFloat()
    };
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