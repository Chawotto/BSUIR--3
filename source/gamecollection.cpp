#include "header/gamecollection.h"
#include <algorithm>

void GameCollection::addGame(const Game& game) {
    games.push_back(game);
}

void GameCollection::removeGame(const std::string& gameName) {
    games.erase(std::ranges::remove_if(games,
                                       [&](const Game& game) { return game.getName() == gameName; }).begin(),
                 games.end());
}

Game* GameCollection::findGame(const std::string_view& gameName) {
    for (auto& game : games) {
        if (game.getName() == gameName) {
            return &game;
        }
    }
    return nullptr;
}

std::vector<Game>::iterator GameCollection::begin() {
    return games.begin();
}

std::vector<Game>::iterator GameCollection::end() {
    return games.end();
}

