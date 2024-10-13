#include "header/registrationwindow.h"
#include "ui_RegistrationWindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "header/User.h"
#include "header/mainwindow.h"

RegistrationWindow::RegistrationWindow(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent), ui(new Ui::RegistrationWindow), mainWindow(mainWin) {
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &RegistrationWindow::saveUser);
    connect(ui->backButton, &QPushButton::clicked, this, &RegistrationWindow::on_backButton_clicked);
}

RegistrationWindow::~RegistrationWindow() {
    delete ui;
}

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

    QFile file("users.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QString::fromStdString(newUser.getName()) << ","
            << QString::fromStdString(password.toStdString()) << ","
            << newUser.getAge() << ","
            << QString::fromStdString(newUser.getGender()) << ","
            << QString::fromStdString(role.toStdString()) << "\n";
        file.close();
        QMessageBox::information(this, "Saving", "User saved successfully");
    } else {
        QMessageBox::warning(this, "Error", "Opening file error occupied.");
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