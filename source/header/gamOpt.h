//
// Created by Morra on 08.09.2024.
//

#ifndef MORRS_GAM_OPT_H
#define MORRS_GAM_OPT_H

#endif //MORRS_GAM_OPT_H

#include <string>
#include "Game.h"
#include <vector>

void deleteGameFromGamerFile(const std::string_view& name, const std::string& filename);
bool addGameToLibrary(const std::string_view& game_name, const std::string& userFileName);
void updateGameInGamerFile(const std::vector<Game>& games, const std::string& filename);