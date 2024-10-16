//
// Created by alexe on 16.10.2024.
//

#include "header/developerUser.h"

DeveloperUser::DeveloperUser(std::string userName, int userAge, std::string userGender): User(std::move(userName),
    userAge, std::move(userGender), userRole::Developer), createdGamesCount(0) {
}
