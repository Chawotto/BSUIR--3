//
// Created by alexe on 17.10.2024.
//

#ifndef GAMERUSER_H
#define GAMERUSER_H

#endif //GAMERUSER_H

#include "User.h"

class GamerUser final : public User {
public:
    GamerUser(std::string userName, int userAge, std::string userGender)
        : User(std::move(userName), userAge, std::move(userGender), userRole::Gamer) {}

    void displayInfo() const override {
        std::cout << "Gamer Info: ";
        User::displayInfo();
    }
};
