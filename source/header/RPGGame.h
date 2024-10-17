//
// Created by alexe on 17.10.2024.
//

#ifndef RPGGAME_H
#define RPGGAME_H

#endif //RPGGAME_H

#include "Game.h"

class RPGGame final : public Game {
public:
    RPGGame(std::string n, float w, float c)
        : Game(std::move(n), "RPG", versions::Release_Candidate, w, c) {}

    void display() const override {
        std::cout << "RPG Game: " << getName() << ", Weight: " << getWeight() << ", Cost: " << getCost() << std::endl;
    }
};