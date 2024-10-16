//
// Created by alexe on 16.10.2024.
//

#ifndef GAMEPROFILE_H
#define GAMEPROFILE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class GameProfile; }
QT_END_NAMESPACE

class GameProfile : public QWidget {
Q_OBJECT

public:
    explicit GameProfile(QWidget *parent = nullptr);
    ~GameProfile() override;

private:
std::unique_ptr<Ui::GameProfile> ui;
};


#endif //GAMEPROFILE_H
