#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

enum class versions {
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

public:
    Game(const std::string& n, const std::string& g, versions v, float w, float c)
            : name(n), genre(g), version(v), weight(w), cost(c) {}

    void saveToFile(std::ofstream& out) const {
        out << name << '\n' << genre << '\n' << std::to_underlying(version) << '\n'
            << weight << '\n' << cost << '\n';
    }

    friend void updateGameInFile(const std::vector<Game>& games, const std::string& filename);

    [[nodiscard]] std::string versionToString() const {
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

    void display() const;
    void updateVersion(versions newVersion);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getGenre() const;
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] float getCost() const;

    [[nodiscard]] std::string toString() const {
        return "Name: " + name + ", Genre: " + genre +
               ", Version: " + versionToString() +
               ", Weight: " + std::to_string(weight) + " Gb, Cost: $" + std::to_string(cost);
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.toString();
        return os;
    }

    bool operator==(const Game& other) const = default;

    Game& operator=(const Game& other) {
        if (this != &other) {
            name = other.name;
            genre = other.genre;
            version = other.version;
            weight = other.weight;
            cost = other.cost;
        }
        return *this;
    }
};