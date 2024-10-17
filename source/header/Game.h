#pragma once
#include <string>
#include <format>
#include <iostream>

enum class versions {
    Pre_Alpha,
    Alfa,
    Beta,
    Release_Candidate,
    General_Availability
};

class Game {
private:
    std::string name;
    std::string genre;
    versions version;
    float weight;
    float cost;

public:
    Game(std::string n, std::string g, versions v, float w, float c)
        : name(std::move(n)), genre(std::move(g)), version(v), weight(w), cost(c) {}

    virtual ~Game() = default;

    void saveToFile(const std::string& filename) const;
    static Game readFromFile(const std::string& filename);

    virtual void display() const {
        std::cout << "Game: " << name << ", Genre: " << genre << ", Version: " << versionToString()
                  << ", Weight: " << weight << ", Cost: " << cost << std::endl;
    }

    void updateVersion(versions newVersion);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getGenre() const;
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] float getCost() const;
    [[nodiscard]] std::string versionToString() const;
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] versions getVersion() const { return version; }

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.toString();
        return os;
    }

    bool operator==(const Game& other) const = default;
};
