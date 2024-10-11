//
// Created by Morra on 08.09.2024.
//

#ifndef MORRS_GAM_OPT_H
#define MORRS_GAM_OPT_H

#endif //MORRS_GAM_OPT_H

#include <string>
#include "Game.h"
#include <vector>

void buyGame();

void readLibrary();

void findGameGam();

void deleteGameFromGamerFile(const string_view& name, const string& filename);

bool addGameToLibrary(const string_view& game_name);

void updateGameInGamerFile(const vector<Game>& games, const string& filename);