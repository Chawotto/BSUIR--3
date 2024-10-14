#pragma once
#include <string>
#include <format>

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
    Game(std::string  n, std::string  g, versions v, float w, float c);

    void saveToFile(std::ofstream& out) const;
    static Game readFromFile(std::ifstream& in);

    void display() const;
    void updateVersion(versions newVersion);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getGenre() const;
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] float getCost() const;
    [[nodiscard]] std::string versionToString() const;
    [[nodiscard]] std::string toString() const;


    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << game.toString();
        return os;
    }

    bool operator==(const Game& other) const = default;
};
