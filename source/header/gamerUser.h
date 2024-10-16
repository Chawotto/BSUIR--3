//
// Created by alexe on 16.10.2024.
//

#ifndef GAMERUSER_H
#define GAMERUSER_H

#endif //GAMERUSER_H

#include <string>
#include "User.h"

class GamerUser : public User {
private:
    int countGamesInLabrary;
    std::string favoriteGame;

public:
    GamerUser(std::string userName, int userAge, std::string userGender);
};