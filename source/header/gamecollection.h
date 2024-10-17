#ifndef GAMECOLLECTION_H
#define GAMECOLLECTION_H

#include "Game.h"
#include <vector>
#include <iterator>

class GameIterator;

class GameCollection {
public:
    void addGame(const Game& game);
    void removeGame(const std::string& gameName);
    Game* findGame(const std::string_view& gameName);

    std::vector<Game>::iterator begin();
    std::vector<Game>::iterator end();

    [[nodiscard]] size_t size() const { return games.size(); }

    Game& getGame(const size_t index) { return games.at(index); }
    [[nodiscard]] const Game& getGame(const size_t index) const { return games.at(index); } // Константная версия

private:
    std::vector<Game> games;
};

#endif // GAMECOLLECTION_H