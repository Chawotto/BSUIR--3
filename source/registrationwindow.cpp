#include "header/registrationwindow.h"
#include "ui_RegistrationWindow.h"
#include <QFile>
#include <QMessageBox>
#include <json/json.h>
#include "header/User.h"
#include "header/mainwindow.h"

RegistrationWindow::RegistrationWindow(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent),
    ui(std::make_unique<Ui::RegistrationWindow>()),
    mainWindow(mainWin) {
    ui->setupUi(this);

    QPixmap background("C:/Users/alexe/Desktop/MorrsQT/source/Images/background.png");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    connect(ui->saveButton, &QPushButton::clicked, this, &RegistrationWindow::saveUser);
    connect(ui->backButton, &QPushButton::clicked, this, &RegistrationWindow::on_backButton_clicked);
}

RegistrationWindow::~RegistrationWindow() = default;

void RegistrationWindow::saveUser() {
    QString name = ui->nameLineEdit->text();

    bool ageOk;
    int age = ui->ageLineEdit->text().toInt(&ageOk);
    if (!ageOk || age <= 0) {
        QMessageBox::warning(this, "Error", "Enter age correctly.");
        return;
    }

    QString password = ui->passwordLineEdit->text();
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty.");
        return;
    }

    QString gender = ui->genderComboBox->currentText();
    QString role = ui->roleComboBox->currentText();

    User newUser;
    newUser.setName(name.toStdString());
    newUser.setAge(age);
    newUser.setGender(gender.toStdString());
    newUser.setRole(roleToEnum(role));

    QFile file("users.json");
    Json::Value jsonData;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        file.close();

        Json::CharReaderBuilder readerBuilder;
        std::string errs;
        std::istringstream s(fileData.toStdString());
        Json::parseFromStream(readerBuilder, s, &jsonData, &errs);
    }

    Json::Value jsonUser;
    jsonUser["name"] = newUser.getName();
    jsonUser["password"] = password.toStdString();
    jsonUser["age"] = newUser.getAge();
    jsonUser["gender"] = newUser.getGender();
    jsonUser["role"] = role.toStdString();

    jsonData.append(jsonUser);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        Json::StreamWriterBuilder writerBuilder;
        std::string outputConfig = Json::writeString(writerBuilder, jsonData);
        file.write(QString::fromStdString(outputConfig).toUtf8());
        file.close();
        QMessageBox::information(this, "Saving", "User saved successfully");
    } else {
        QMessageBox::warning(this, "Error", "Opening file error occurred.");
    }
}

userRole RegistrationWindow::roleToEnum(const QString &role) {
    using enum userRole;
    if (role == "Developer") return Developer;
    if (role == "Gamer") return Gamer;
    if (role == "Administrator") return Administrator;
    return Gamer;
}

void RegistrationWindow::clearInputs() {
    ui->passwordLineEdit->clear();
    ui->ageLineEdit->clear();
    ui->nameLineEdit->clear();
}

void RegistrationWindow::on_backButton_clicked() {
    ui->nameLineEdit->clear();
    ui->ageLineEdit->clear();
    ui->passwordLineEdit->clear();
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}