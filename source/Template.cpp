#include "header/Template.h"
#include <memory>
#include "header/DeveloperUser.h"
#include "header/GamerUser.h"
#include "header/User.h"

void exampleUsage() {
    UserContainer<User> userContainer;

    auto devUser = std::make_shared<DeveloperUser>("Alice", 30, "Female");
    auto gamerUser = std::make_shared<GamerUser>("Bob", 25, "Male");

    userContainer.addUser(devUser);
    userContainer.addUser(gamerUser);

    userContainer.displayAll();
}