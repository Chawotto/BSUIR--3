#include <string>
#include "header/User.h"

using namespace std;

User::~User() = default;

void User::setName(const string_view& userName) {
    name = userName;
}

void User::setAge(int userAge) {
    age = userAge;
}

void User::setGender(const string_view& userGender) {
    gender = userGender;
}

void User::setRole(userRole userRole) {
    role = userRole;
}

void User::setPassword(const string_view& userPassword) {
    password = userPassword;
}

string User::getName() const {
    return name;
}

int User::getAge() const {
    return age;
}

string User::getGender() const {
    return gender;
}

userRole User::getRole() const {
    return role;
}

string User::getPassword() {
    return password;
}

string User::roleAsString() const {
    return roleToString();
}
