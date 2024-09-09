//
// Created by Morra on 07.09.2024.
//

#ifndef MORRS_DEV_OPT_H
#define MORRS_DEV_OPT_H
#endif //MORRS_DEV_OPT_H
#include <string>
#include <fstream>
#include <iostream>

enum class versions{
    Pre_Alpha,
    Alfa,
    Beta,
    Release_candidate,
    General_availability
};

class Game {
private:
    std::string name;
    std::string genre;
    versions version;
    float weight;
    float cost;
    friend versions;

    std::string versionToString() const {
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

    Game(const std::string& n, const std::string& g, versions v, float w, float c)
    : name(n), genre(g), version(v), weight(w), cost(c) {}

    void saveToFile(std::ofstream& out) const {
        out << name << '\n' << genre << '\n' << static_cast<int>(version) << '\n'
            << weight << '\n' << cost << '\n';
    }

    static Game readFromFile(std::ifstream& in) {
        std::string n;
        std::string g;
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
        std::cout << "Name: " << name << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Version: " << versionToString() << std::endl;
        std::cout << "Weight: " << weight << "Gb" << std::endl;
        std::cout << "Cost: " << cost << "$" << std::endl;
        std::cout << "\n";
    }
};

void createGame();
void readGames();
void deleteGameFromFile(const std::string_view& name, const std::string& filename);
void findGameDev();