#include "header/enterwindow.h"
#include "ui_EnterWindow.h"
#include "header/mainwindow.h"
#include "header/developermenu.h"
#include "header/gamermenu.h"
#include <QFile>
#include <QMessageBox>
#include <memory>

EnterWindow::EnterWindow(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent), ui(new Ui::EnterWindow), mainWindow(mainWin) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &EnterWindow::on_loginButton_clicked);
}

EnterWindow::~EnterWindow() = default;

void EnterWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл пользователей.");
        return;
    }

    QString line;
    std::unique_ptr<QWidget> menu;
    while (!file.atEnd()) {
        line = file.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 5) {
            QString storedUsername = fields[0].trimmed();
            QString storedPassword = fields[1].trimmed();
            QString userRole = fields[4].trimmed();

            if (storedUsername == username && storedPassword == password) {
                if (userRole == "Developer") {
                    menu = std::make_unique<DeveloperMenu>(mainWindow, this, username);
                } else if (userRole == "Gamer") {
                    menu = std::make_unique<GamerMenu>(mainWindow, this, username);
                }
                break;
            }
        }
    }

    file.close();

    if (menu) {
        menu->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль.");
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