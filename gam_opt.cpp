//
// Created by Morra on 08.09.2024.
//

#include "gam_opt.h"
#include "dev_opt.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
void print (const T& word) {
    cout << word << endl;
}

bool add_game_to_library(const string_view& game_name);

void buy_game() {
    readGames();
    string enter_name;
    cout << "Enter the game name to buy it and add to library: ";
    _flushall();
    getline(cin, enter_name);

    if (add_game_to_library(enter_name)) {
        cout << "Game added to library." << endl;
    } else {
        cout << "Game not found." << endl;
    }
}

bool add_game_to_library(const string_view& game_name) {
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

void read_library() {
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
            cout << "Version: " << static_cast<int>(static_cast<versions>(versionInt)) << endl;
            cout << "Weight: " << weight << "Gb" << endl;
            cout << "Cost: " << cost << "$" << endl;
            cout << "\n";
        }
        in.close();
    } else {
        cout << "Error opening library file for reading." << endl;
    }
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