#include "header/gameIterator.h"

GameIterator::GameIterator(GameCollection const &collection) : collection(collection){}

Game GameIterator::next() {
    Game game = collection.getGame(index);
    ++index;
    return game;
}