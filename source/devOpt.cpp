//
// Created by Morra on 07.09.2024.
//

#include "header/Game.h"
#include "header/devOpt.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h> // Подключаем jsoncpp

using namespace std;

void updateGameInFile(const std::vector<Game>& games, const std::string& filename) {
    Json::Value jsonData;

    for (const auto& game : games) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();

        switch (game.getVersion()) {
            case versions::Pre_Alpha:
                jsonGame["version"] = "Pre_Alpha";
            break;
            case versions::Alfa:
                jsonGame["version"] = "Alfa";
            break;
            case versions::Beta:
                jsonGame["version"] = "Beta";
            break;
            case versions::Release_Candidate:
                jsonGame["version"] = "Release_Candidate";
            break;
            case versions::General_Availability:
                jsonGame["version"] = "General_Availability";
            break;
        }

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
            std::string versionStr = jsonGame["version"].asString();

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
                continue;
            }

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
