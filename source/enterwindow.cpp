#include "header/enterwindow.h"
#include "ui_EnterWindow.h"
#include "header/mainwindow.h"
#include "header/developermenu.h"
#include "header/gamermenu.h"
#include <QFile>
#include <QMessageBox>
#include <memory>
#include <json/json.h>

EnterWindow::EnterWindow(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent),
    ui(std::make_unique<Ui::EnterWindow>()),
    mainWindow(mainWin) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &EnterWindow::on_loginButton_clicked);

    QPixmap background("C:/Users/alexe/Desktop/MorrsQT/source/Images/background.png");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

EnterWindow::~EnterWindow() = default;

void EnterWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (!validateUser(username, password)) {
        QMessageBox::warning(this, "Error", "Invalid username or password");
    }
}

bool EnterWindow::validateUser(const QString &username, const QString &password) {
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Error opening file");
        return false;
    }

    QByteArray fileData = file.readAll();
    file.close();

    Json::Value jsonData;
    Json::CharReaderBuilder reader;
    std::string errs;

    if (std::stringstream ss(fileData.toStdString()); !parseFromStream(reader, ss, &jsonData, &errs)) {
        QMessageBox::critical(this, "Error", "Error parsing JSON: " + QString::fromStdString(errs));
        return false;
    }

    bool validUser = std::ranges::any_of(jsonData, [&](const auto& user) {
        QString storedUsername = QString::fromStdString(user["name"].asString()).trimmed();
        QString storedPassword = QString::fromStdString(user["password"].asString()).trimmed();
        QString userRole = QString::fromStdString(user["role"].asString()).trimmed();

        if (storedUsername == username && storedPassword == password) {
            openUserMenu(userRole, username);
            return true;
        }
        return false;
    });

    return validUser;
}


void EnterWindow::openUserMenu(const QString &userRole, const QString &username) {
    if (userRole == "Developer") {
        menu = std::make_unique<DeveloperMenu>(mainWindow, this, username);
    } else if (userRole == "Gamer") {
        menu = std::make_unique<GamerMenu>(mainWindow, this, username);
    }

    if (menu) {
        menu->show();
        this->close();
    }
}

void EnterWindow::clearInputs() const {
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
}

void EnterWindow::on_backButton_clicked() {
    clearInputs();
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}