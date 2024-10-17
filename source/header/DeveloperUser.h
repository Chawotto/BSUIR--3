//
// Created by alexe on 17.10.2024.
//

#ifndef DEVELOPERUSER_H
#define DEVELOPERUSER_H

#endif //DEVELOPERUSER_H
#include "User.h"

class DeveloperUser final : public User {
public:
    DeveloperUser(std::string userName, int userAge, std::string userGender)
        : User(std::move(userName), userAge, std::move(userGender), userRole::Developer) {}

    void displayInfo() const override {
        std::cout << "Developer Info: ";
        User::displayInfo();
    }
};