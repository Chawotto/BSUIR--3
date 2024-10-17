#ifndef USEREXCEPTION_H
#define USEREXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class UserException final : public std::exception {
private:
    std::string message;

public:
    explicit UserException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // USEREXCEPTION_H