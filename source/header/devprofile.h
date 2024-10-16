//
// Created by alexe on 16.10.2024.
//

#ifndef DEVPROFILE_H
#define DEVPROFILE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class devProfile; }
QT_END_NAMESPACE

class devProfile : public QWidget {
Q_OBJECT

public:
    explicit devProfile(QWidget *parent = nullptr);
    ~devProfile() override;

private:
std::unique_ptr<Ui::devProfile> ui;
};


#endif //DEVPROFILE_H
