//
// Created by alexe on 17.10.2024.
//

#ifndef USEREXCEPRION_H
#define USEREXCEPRION_H

#endif //USEREXCEPRION_H

#include <exception>
#include <string>

class UserException : public std::exception {
private:
    std::string message;

public:
    explicit UserException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};