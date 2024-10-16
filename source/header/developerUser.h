//
// Created by alexe on 16.10.2024.
//

#ifndef DEVELOPERUSER_H
#define DEVELOPERUSER_H
#endif //DEVELOPERUSER_H

#include "User.h"
#include <string>


class DeveloperUser : public User {
private:
    std::string level;
    std::string company;
    int createdGamesCount;

public:
    DeveloperUser(std::string userName, int userAge, std::string userGender);
};