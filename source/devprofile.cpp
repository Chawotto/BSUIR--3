//
// Created by alexe on 16.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_devProfile.h" resolved

#include "header/devprofile.h"
#include "ui_devProfile.h"


devProfile::devProfile(QWidget *parent) :
    QWidget(parent), ui(std::make_unique <Ui::devProfile>()) {
    ui->setupUi(this);
}

devProfile::~devProfile() = default;
