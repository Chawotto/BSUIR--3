//
// Created by alexe on 17.10.2024.
//

#ifndef TEMPLATE_H
#define TEMPLATE_H

#endif //TEMPLATE_H
#include <vector>
#include <memory>

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