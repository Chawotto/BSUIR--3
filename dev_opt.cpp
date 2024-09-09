//
// Created by Morra on 07.09.2024.
//

#include "gam_opt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void print (const T& word) {
    cout << word << endl;
}

enum class versions{
    Pre_Alpha,
    Alfa,
    Beta,
    Release_candidate,
    General_availability
};

class Game {
private:
    string name;
    string genre;
    versions version;
    float weight;
    float cost;
    friend versions;

    string versionToString() const {
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
public:

    Game(const string& n, const string& g, versions v, float w, float c)
            : name(n), genre(g), version(v), weight(w), cost(c) {}

    void saveToFile(ofstream& out) const {
        out << name << '\n' << genre << '\n' << static_cast<int>(version) << '\n'
            << weight << '\n' << cost << '\n';
    }

    static Game readFromFile(ifstream& in) {
        string n;
        string g;
        int v;
        float w;
        float c;

        getline(in, n);
        getline(in, g);
        in >> v >> w >> c;
        in.ignore();

        return Game(n, g, static_cast<versions>(v), w, c);
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Genre: " << genre << endl;
        cout << "Version: " << versionToString() << endl;
        cout << "Weight: " << weight << "Gb" << endl;
        cout << "Cost: " << cost << "$" << endl;
        print("\n");
    }

    void updateVersion(versions newVersion) {
        version = newVersion;
    }

    string getName() const {
        return name;
    }
};

void createGame() {
    string name;
    string genre;
    int versionInt;
    float weight;
    float cost;

    cout << "Enter game name: ";
    _flushall();
    getline(cin,name);
    cout << "Enter game genre: ";
    _flushall();
    getline(cin,genre);
    cout << "Enter game version (0: Pre_Alpha, 1: Alfa, 2: Beta, 3: Release_candidate, 4: General_availability): ";
    cin >> versionInt;
    cout << "Enter game weight (Gb): ";
    cin >> weight;
    cout << "Enter game cost ($): ";
    cin >> cost;

    Game game(name, genre, static_cast<versions>(versionInt), weight, cost);

    ofstream out("games.txt", ios::app);
    if (out.is_open()) {
        game.saveToFile(out);
        out.close();
        cout << "Game information saved to file." << endl;
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

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

void modifyGame(Game& game) {
    print("Enter new version (0: Pre_Alpha, 1: Alfa, 2: Beta, 3: Release_candidate, 4: General_availability): ");
    int newVersionInt;
    cin >> newVersionInt;
    game.updateVersion(static_cast<versions>(newVersionInt));
}

void readGames() {
    ifstream in("games.txt");
    if (!in.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    vector<Game> games;
    while (in.good()) {
        Game game = Game::readFromFile(in);
        if (in.good()) {
            games.push_back(game);
        }
    }
    in.close();

    for (const auto& game: games) {
        game.display();
    }
}



void findGameDev() {
    string name;
    cout << "Enter the name of the game to find: ";
    cin.ignore();
    getline(cin, name);

    ifstream in("games.txt");
    vector<Game> games;
    bool find = false;

    if (in.is_open()) {
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                games.push_back(game);
            }
        }
        in.close();
    } else {
        cout << "Error opening file for reading." << endl;
        return;
    }

    for (auto& game : games) {
        if (game.getName() == name) {
            find = true;
            game.display();

            print("1. Update Game");
            print("2. Delete Game");
            print("0. Back");
            cout << "Choose an option: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                modifyGame(game);
                updateGameInFile(games, "games.txt");
                updateGameInFile(games, "library.txt");
                cout << "Game updated." << endl;
            } else if (choice == 2) {
                deleteGameFromFile(name, "games.txt");
                deleteGameFromFile(name, "library.txt");
                cout << "Game deleted." << endl;
            } else if (choice == 0) {
                break;
            }
        }
    }
    if (!find) {
        print("Invalid game name");
    }
}

