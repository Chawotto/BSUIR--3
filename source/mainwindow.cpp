#include "header/mainwindow.h"
#include "ui_MainWindow.h"
#include "header/enterwindow.h"
#include "header/registrationwindow.h"
#include <ui_EnterWindow.h>
#include <ui_RegistrationWindow.h>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QPixmap logo("C:/Users/alexe/Desktop/MorrsQT/source/Images/logo.png");
    ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    connect(ui->signInButton, &QPushButton::clicked, this, &MainWindow::on_signInButton_clicked);
    connect(ui->signUpButton, &QPushButton::clicked, this, &MainWindow::on_signUpButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_signInButton_clicked() {
    if (!enterWindow) {
        enterWindow = new EnterWindow(this);
    }
    enterWindow->clearInputs();
    enterWindow->show();
}

void MainWindow::on_signUpButton_clicked() {
    if (!registrationWindow) {
        registrationWindow = new RegistrationWindow(this);
    }
    registrationWindow->clearInputs();
    registrationWindow->show();
}

void MainWindow::on_exitButton_clicked() {
    close();
}