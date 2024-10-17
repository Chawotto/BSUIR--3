//
// Created by alexe on 17.10.2024.
//

#ifndef GAMEITERATOR_H
#define GAMEITERATOR_H

#include "gamecollection.h"

#endif //GAMEITERATOR_H

class GameIterator {
public:
    explicit GameIterator(GameCollection const& collection);

    [[nodiscard]] bool hasNext() const {
        return index < collection.size();
    }

    Game next();

private:
    const GameCollection& collection;
    size_t index = 0;
    bool isConst = false;
};

