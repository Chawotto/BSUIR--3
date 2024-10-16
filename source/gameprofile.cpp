//
// Created by alexe on 16.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameProfile.h" resolved

#include "header/gameprofile.h"
#include "ui_GameProfile.h"


GameProfile::GameProfile(QWidget *parent) :
    QWidget(parent), ui(std::make_unique <Ui::GameProfile>()) {
    ui->setupUi(this);
}

GameProfile::~GameProfile() = default;
