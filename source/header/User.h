#ifndef USER_H
#define USER_H

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <memory>

class UserException : public std::exception {
private:
    std::string message;

public:
    explicit UserException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

enum class userRole {
    Developer,
    Gamer,
    Administrator
};

class AbstractUser {
public:
    virtual void displayInfo() const = 0;
    virtual ~AbstractUser() = default;
};

class User : public AbstractUser {
private:
    std::string name;
    int age;
    std::string gender;
    userRole role;
    std::string password;

    [[nodiscard]] std::string roleToString() const {
        switch (role) {
            using enum userRole;
            case Developer: return "Developer";
            case Gamer: return "Gamer";
            case Administrator: return "Administrator";
            default: return "Unknown";
        }
    }

public:
    User() : age(0), role(userRole::Gamer) {}

    User(std::string userName, int userAge, std::string userGender, userRole userRole)
        : name(std::move(userName)), age(userAge), gender(std::move(userGender)), role(userRole) {
        if (age < 0) {
            throw UserException("Age cannot be negative.");
        }
        if (name.empty()) {
            throw UserException("Name cannot be empty.");
        }
    }

    void displayInfo() const override {
        std::cout << "Name: " << name << ", Age: " << age
                  << ", Gender: " << gender << ", Role: " << roleToString() << std::endl;
    }

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

class DeveloperUser : public User {
public:
    DeveloperUser(std::string userName, int userAge, std::string userGender)
        : User(std::move(userName), userAge, std::move(userGender), userRole::Developer) {}

    void displayInfo() const override {
        std::cout << "Developer Info: ";
        User::displayInfo();
    }
};

class GamerUser : public User {
public:
    GamerUser(std::string userName, int userAge, std::string userGender)
        : User(std::move(userName), userAge, std::move(userGender), userRole::Gamer) {}

    void displayInfo() const override {
        std::cout << "Gamer Info: ";
        User::displayInfo();
    }
};

class AdminUser : public User {
public:
    AdminUser(std::string userName, int userAge, std::string userGender)
        : User(std::move(userName), userAge, std::move(userGender), userRole::Administrator) {}

    void displayInfo() const override {
        std::cout << "Admin Info: ";
        User::displayInfo();
    }
};

template<typename T>
class UserContainer {
private:
    std::vector<std::shared_ptr<T>> users;

public:
    void addUser(const std::shared_ptr<T>& user) {
        users.push_back(user);
    }

    void displayAll() const {
        for (const auto& user : users) {
            user->displayInfo();
        }
    }
};

#endif // USER_H

//void exampleUsage() {
    //UserContainer<User> userContainer;

    //auto devUser = std::make_shared<DeveloperUser>("Alice", 30, "Female");
    //auto gamerUser = std::make_shared<GamerUser>("Bob", 25, "Male");
    //auto adminUser = std::make_shared<AdminUser>("Charlie", 35, "Other");

    //userContainer.addUser(devUser);
    //userContainer.addUser(gamerUser);
    //userContainer.addUser(adminUser);

    //userContainer.displayAll();
//}
USER_H