//
// Created by Morra on 07.09.2024.
//

#ifndef MORRS_DEV_OPT_H
#define MORRS_DEV_OPT_H
#endif //MORRS_DEV_OPT_H

#include <string>
#include "Game.h"
#include <vector>

void deleteGameFromFile(const std::string_view& name, const std::string& filename);
void updateGameInFile(const std::vector<Game>& games, const std::string& filename);