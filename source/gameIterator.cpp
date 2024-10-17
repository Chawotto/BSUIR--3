#include "header/gameIterator.h"

GameIterator::GameIterator(GameCollection const &collection) : collection(collection), isConst(false) {}

Game GameIterator::next() {
    Game game = collection.getGame(index);
    ++index;
    return game;
}