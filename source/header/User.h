#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

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
    string password;

    [[nodiscard]] string roleToString() const {
        switch (role) {
            using enum userRole;
            case userRole::Developer:
                return "Developer";
            case userRole::Gamer:
                return "Gamer";
            case userRole::Administrator:
                return "Administrator";
            default:
                return "Unknown";
        }
    }

public:

    User() : age(0), role(userRole::Gamer) {}

    User(string  userName, int userAge, string  userGender, userRole userRole)
        : name(std::move(userName)), age(userAge), gender(std::move(userGender)), role(userRole) {}

    void setName(const string_view& userName);
    void setAge(int userAge);
    void setGender(const string_view& userGender);
    void setRole(userRole userRole);
    void setPassword(const string_view& userPassword);
    [[nodiscard]] string getName() const;
    [[nodiscard]] int getAge() const;
    [[nodiscard]] string getGender() const;
    [[nodiscard]] userRole getRole() const;
    [[nodiscard]] string getPassword() const;
    [[nodiscard]] string roleAsString() const;
};

#endif // USER_H