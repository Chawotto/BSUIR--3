//
// Created by Morra on 08.09.2024.
//

#include "header/devOpt.h"
#include "header/Game.h"
#include "header/gamOpt.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool addGameToLibrary(const string_view& game_name, const string& userFileName);

bool addGameToLibrary(const string_view& game_name, const string& userFileName) {
    ifstream in("games.txt");
    string name;
    string genre;
    int versionInt;
    float weight;
    float cost;
    bool found = false;

    if (!in.is_open()) {
        return false;
    }
    while (getline(in, name)) {
        getline(in, genre);
        in >> versionInt >> weight >> cost;
        in.ignore();
        if (name == game_name) {
            found = true;
            if (ofstream out(userFileName, ios::app); out.is_open()) { // Используем файл пользователя
                Game game(name, genre, static_cast<versions>(versionInt), weight, cost);
                game.saveToFile(out);
                out.close();
            } else {
                cout << "Error opening library file for writing." << endl;
            }
            break;
        }
    }
    in.close();

    return found;
}

void updateGameInGamerFile(const vector<Game>& games, const string& filename) {
    ofstream out(filename);
    if (out.is_open()) {
        for (const auto& game : games) {
            game.saveToFile(out);
        }
        out.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

void deleteGameFromGamerFile(const string_view& name, const string& filename) {
    ifstream in(filename);
    vector<Game> games;

    if (in.is_open()) {
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good() && game.getName() != name) {
                games.push_back(game);
            }
        }
        in.close();
    }

    updateGameInGamerFile(games, filename);
}
