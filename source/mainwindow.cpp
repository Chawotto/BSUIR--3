#include "header/mainwindow.h"
#include "ui_MainWindow.h"
#include "header/gamermenu.h"
#include "header/developermenu.h"
#include <ui_DeveloperMenu.h>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QPixmap logo("C:/Users/alexe/Desktop/MorrsQT/source/Images/logo.png");
    ui->logoLabel->setPixmap(logo.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    connect(ui->developerButton, &QPushButton::clicked, this, &MainWindow::on_developerButton_clicked);
    connect(ui->gamerButton, &QPushButton::clicked, this, &MainWindow::on_gamerButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_developerButton_clicked() {
    if (!developerMenu) {
        developerMenu = new DeveloperMenu(this);
    }
    developerMenu->show();
}

void MainWindow::on_gamerButton_clicked() {
    if (!gamerMenu) {
        gamerMenu = new GamerMenu(this);
    }
    gamerMenu->show();
}

void MainWindow::on_exitButton_clicked() {
    close();
}