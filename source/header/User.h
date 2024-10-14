#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

enum class userRole {
    Developer,
    Gamer,
    Administrator
};

class User {
private:
    std::string name;
    int age;
    std::string gender;
    userRole role;
    std::string password;

    [[nodiscard]] std::string roleToString() const {
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

    User(std::string  userName, int userAge, std::string  userGender, userRole userRole)
        : name(std::move(userName)), age(userAge), gender(std::move(userGender)), role(userRole) {}

    void setName(const std::string_view& userName);
    void setAge(int userAge);
    void setGender(const std::string_view& userGender);
    void setRole(userRole userRole);
    void setPassword(const std::string_view& userPassword);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getAge() const;
    [[nodiscard]] std::string getGender() const;
    [[nodiscard]] userRole getRole() const;
    [[nodiscard]] std::string getPassword() const;
    [[nodiscard]] std::string roleAsString() const;
};

#endif // USER_H