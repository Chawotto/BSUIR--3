#include "header/gameprofile.h"
#include "ui_GameProfile.h"


GameProfile::GameProfile(QWidget *parent) :
    QWidget(parent), ui(std::make_unique <Ui::GameProfile>()) {
    ui->setupUi(this);
}

GameProfile::~GameProfile() = default;
