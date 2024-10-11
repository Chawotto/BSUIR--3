//
// Created by Morra on 08.09.2024.
//

#include "header/devOpt.h"
#include "header/Game.h"
#include "header/gamOpt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

template <typename T>
void print (const T& word) {
    cout << word << endl;
}

bool addGameToLibrary(const string_view& game_name);

void buyGame() {
    readGames();
    string enter_name;
    cout << "Enter the game name to buy it and add to library: ";
    _flushall();
    getline(cin, enter_name);

    if (addGameToLibrary(enter_name)) {
        cout << "Game added to library." << endl;
    } else {
        cout << "Game not found." << endl;
    }
}

bool addGameToLibrary(const string_view& game_name) {
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
            if (ofstream out("library.txt", ios::app); out.is_open()) {
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

void readLibrary() {
    ifstream in("library.txt");
    string name;
    string genre;
    int versionInt;
    float weight;
    float cost;

    if (in.is_open()) {
        while (getline(in, name)) {
            getline(in, genre);
            in >> versionInt >> weight >> cost;
            in.ignore();
            cout << "Name: " << name << endl;
            cout << "Genre: " << genre << endl;
            cout << "Version: " << std::to_underlying(static_cast<versions>(versionInt)) << endl;
            cout << "Weight: " << weight << "Gb" << endl;
            cout << "Cost: " << cost << "$" << endl;
            cout << "\n";
        }
        in.close();
    } else {
        cout << "Error opening library file for reading." << endl;
    }
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

void findGameGam() {
    string name;
    cout << "Enter the name of the game to find: ";
    cin.ignore();
    getline(cin, name);

    ifstream in("library.txt");
    if (!in.is_open()) {
        return;
    }
    string line;
    bool find = false;
    while (getline(in, line)) {
        if (line == name) {
            find = true;
            string genre;
            int versionInt;
            float weight;
            float cost;

            getline(in, genre);
            in >> versionInt >> weight >> cost;
            in.ignore();

            Game game(name, genre, static_cast<versions>(versionInt), weight, cost);
            game.display();

            print("1. Delete Game");
            print("0. Back");
            cout << "Choose an option: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    deleteGameFromFile(name, "library.txt");
                    cout << "Game deleted." << endl;
                    break;
                case 0:
                    break;
                default:
                    print("Invalid Option");
                    break;
            }

        } else {
            getline(in, line);
            in >> line;
            in >> line;
            in >> line;
            in.ignore();
        }
    }
    in.close();
    if (!find) {
        print("Invalid game name");
    }
}