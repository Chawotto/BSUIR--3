#include "header/Game.h"
#include "header/devOpt.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h>

using namespace std;

versions stringToVersion(const std::string& versionStr) {
    using enum versions;
    if (versionStr == "Pre_Alpha") return Pre_Alpha;
    if (versionStr == "Alfa") return Alfa;
    if (versionStr == "Beta") return Beta;
    if (versionStr == "Release_Candidate") return Release_Candidate;
    if (versionStr == "General_Availability") return General_Availability;
    throw std::invalid_argument("Unknown version: " + versionStr);
}

std::string versionToString(versions version) {
    switch (version) {
        using enum versions;
        case Pre_Alpha: return "Pre_Alpha";
        case Alfa: return "Alfa";
        case Beta: return "Beta";
        case Release_Candidate: return "Release_Candidate";
        case General_Availability: return "General_Availability";
        default: throw std::invalid_argument("Unknown version");
    }
}

void updateGameInFile(const std::vector<Game>& games, const std::string& filename) {
    Json::Value jsonData;

    for (const auto& game : games) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();
        jsonGame["version"] = versionToString(game.getVersion());
        jsonGame["weight"] = game.getWeight();
        jsonGame["cost"] = game.getCost();
        jsonData.append(jsonGame);
    }

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << jsonData;
        outFile.close();
    } else {
        std::cout << "Error opening file for writing." << std::endl;
    }
}

void deleteGameFromFile(const std::string_view& name, const std::string& filename) {
    std::ifstream in(filename);
    std::vector<Game> games;

    if (in.is_open()) {
        Json::Value jsonData;
        in >> jsonData;

        for (const auto& jsonGame : jsonData) {
            versions version = stringToVersion(jsonGame["version"].asString());

            Game game(
                jsonGame["name"].asString(),
                jsonGame["genre"].asString(),
                version,
                jsonGame["weight"].asFloat(),
                jsonGame["cost"].asFloat()
            );

            if (game.getName() != name) {
                games.push_back(game);
            }
        }
        in.close();
    }

    updateGameInFile(games, filename);
}