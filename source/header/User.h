//
// Created by alexe on 08.10.2024.
//

#ifndef USER_H
#define USER_H

#endif //USER_H

#include <string>

using namespace std;

enum class userRole {
    Developer,
    Gamer,
    Administrator
};

class User {
private:
    string name;
    int age;
    string gender;
    userRole role;
    friend userRole;

    string roleToString() const {
        switch (role) {
            using enum userRole;
            case Developer:
                return "Developer";
            case Gamer:
                return "Gamer";
            case Administrator:
                return "Administrator";
            default:
                return "Unknown";
        }
    }


};