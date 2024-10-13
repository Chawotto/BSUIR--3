#include "header/enterwindow.h"
#include "ui_EnterWindow.h"
#include "header/mainwindow.h"
#include "header/developermenu.h"
#include "header/gamermenu.h"
#include <QFile>
#include <QMessageBox>

EnterWindow::EnterWindow(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent), ui(new Ui::EnterWindow), developerMenu(nullptr), gamerMenu(nullptr), mainWindow(mainWin) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &EnterWindow::on_loginButton_clicked);
}

EnterWindow::~EnterWindow() {
    delete ui;
    delete developerMenu;
    delete gamerMenu;
}

void EnterWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл пользователей.");
        return;
    }

    QString line;
    bool userFound = false;
    while (!file.atEnd()) {
        line = file.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 5) {
            QString storedUsername = fields[0].trimmed();
            QString storedPassword = fields[1].trimmed();
            QString userRole = fields[4].trimmed();

            if (storedUsername == username && storedPassword == password) {
                userFound = true;
                file.close();

                if (userRole == "Developer") {
                    delete developerMenu;
                    developerMenu = new DeveloperMenu(mainWindow, this, username);
                    developerMenu->show();
                } else if (userRole == "Gamer") {
                    delete gamerMenu;
                    gamerMenu = new GamerMenu(mainWindow, this, username);
                    gamerMenu->show();
                }

                this->close();
                return;
            }
        }
    }

    file.close();

    if (!userFound) {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль.");
    }

}

void EnterWindow::clearInputs() const {
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
}

void EnterWindow::on_backButton_clicked() {
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}