#include "header/devOpt.h"
#include "header/Game.h"
#include "header/gamOpt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <json/json.h>

using namespace std;

bool isGameInUserLibrary(const Json::Value& userGamesData, const std::string_view& game_name) {
    std::vector<std::string> gameNames;
    gameNames.reserve(userGamesData.size());

    for (const auto& userGame : userGamesData) {
        gameNames.push_back(userGame["name"].asString());
    }

    return std::ranges::contains(gameNames, game_name);
}

Game createGameFromJson(const Json::Value& jsonGame) {
    using enum versions;
    std::string versionStr = jsonGame["version"].asString();
    versions version;
    if (versionStr == "Pre_Alpha")
        version = Pre_Alpha;
    else
        if (versionStr == "Release_Candidate")
            if (versionStr == "Beta")
                version = versionStr == "Alfa"
                              ? Alfa
                              : Beta;
            else
                version = versionStr == "Alfa"
                              ? Alfa
                              : Release_Candidate;
        else
            if (versionStr == "Beta")
                version = versionStr == "Alfa"
                              ? Alfa
                              : Beta;
            else
                version = versionStr == "Alfa"
                              ? Alfa
                              : General_Availability;

    return Game(
        jsonGame["name"].asString(),
        jsonGame["genre"].asString(),
        version,
        jsonGame["weight"].asFloat(),
        jsonGame["cost"].asFloat()
    );
}

void addGameToUserLibrary(Json::Value& userGamesData, const Game& game) {
    Json::Value jsonGameToAdd;
    jsonGameToAdd["name"] = game.getName();
    jsonGameToAdd["genre"] = game.getGenre();

    switch (game.getVersion()) {
        using enum versions;
        case Pre_Alpha:
            jsonGameToAdd["version"] = "Pre_Alpha";
            break;
        case Alfa:
            jsonGameToAdd["version"] = "Alfa";
            break;
        case Beta:
            jsonGameToAdd["version"] = "Beta";
            break;
        case Release_Candidate:
            jsonGameToAdd["version"] = "Release_Candidate";
            break;
        case General_Availability:
            jsonGameToAdd["version"] = "General_Availability";
            break;
    }

    jsonGameToAdd["weight"] = game.getWeight();
    jsonGameToAdd["cost"] = game.getCost();

    userGamesData.append(jsonGameToAdd);
}

bool writeUserGamesToFile(const std::string& filename, const Json::Value& userGamesData) {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << userGamesData;
        out.close();
        return true;
    }
    std::cout << "Error opening library file for writing." << std::endl;
    return false;
}

void updateGameInGamerFile(const std::vector<Game>& games, const std::string& filename) {
    if (games.empty()) {
        std::cout << "No games to update." << std::endl;
        return;
    }

    Json::Value jsonData;
    for (const auto& game : games) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();

        switch (game.getVersion()) {
            using enum versions;
            case Pre_Alpha:
                jsonGame["version"] = "Pre_Alpha";
            break;
            case Alfa:
                jsonGame["version"] = "Alfa";
            break;
            case Beta:
                jsonGame["version"] = "Beta";
            break;
            case Release_Candidate:
                jsonGame["version"] = "Release_Candidate";
            break;
            case General_Availability:
                jsonGame["version"] = "General_Availability";
            break;
        }

        jsonGame["weight"] = game.getWeight();
        jsonGame["cost"] = game.getCost();
        jsonData.append(jsonGame);
    }

    std::ofstream out(filename);
    if (out.is_open()) {
        out << jsonData;
        out.close();
    } else {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
    }
}

bool addGameToLibrary(const std::string_view& game_name, const std::string& userFileName) {
    std::ifstream in("games.json");
    if (!in.is_open()) {
        std::cout << "Error opening games file." << std::endl;
        return false;
    }

    Json::Value jsonData;
    in >> jsonData;
    in.close();

    Json::Value userGamesData;

    std::ifstream userFile(userFileName);
    if (userFile.is_open()) {
        userFile >> userGamesData;
        userFile.close();
    }

    for (const auto& jsonGame : jsonData) {
        if (jsonGame["name"].asString() == game_name) {
            if (isGameInUserLibrary(userGamesData, game_name)) {
                std::cout << "Game is already in the library." << std::endl;
                return false;
            }

            Game game = createGameFromJson(jsonGame);
            addGameToUserLibrary(userGamesData, game);

            return writeUserGamesToFile(userFileName, userGamesData);
        }
    }

    return false;
}

void deleteGameFromGamerFile(const std::string_view& name, const std::string& filename) {
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<Game> games;
    Json::Value jsonData;
    in >> jsonData;

    bool gameFound = false;

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

        if (game.getName() == name) {
            gameFound = true;
            continue;
        }

        games.push_back(game);
    }
    in.close();

    if (!gameFound) {
        std::cout << "Game not found: " << name << std::endl;
    }

    updateGameInGamerFile(games, filename);
}

