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

using namespace std;

void updateGameInFile(const vector<Game>& games, const string& filename) {
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

void deleteGameFromFile(const string_view& name, const string& filename) {
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

    updateGameInFile(games, filename);
}




