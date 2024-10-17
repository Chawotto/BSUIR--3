//
// Created by alexe on 17.10.2024.
//

#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#endif //GAMEEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class GameException : public std::exception {
private:
    std::string message;

public:
    explicit GameException(std::string  msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};