//
// Created by alexe on 17.10.2024.
//

#ifndef ACTIONGAME_H
#define ACTIONGAME_H

#endif //ACTIONGAME_H

#include "Game.h"

class ActionGame final : public Game {
public:
    ActionGame(std::string n, float w, float c)
        : Game(std::move(n), "Action", versions::Beta, w, c) {}

    void display() const override {
        std::cout << "Action Game: " << getName() << ", Weight: " << getWeight() << ", Cost: " << getCost() << std::endl;
    }
};