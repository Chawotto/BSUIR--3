#include "header/gamermenu.h"
#include "ui_GamerMenu.h"
#include "header/gamOpt.h"
#include "header/Game.h"
#include <QMessageBox>
#include <QInputDialog>
#include "header/mainwindow.h"
#include <fstream>
#include <vector>

GamerMenu::GamerMenu(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent), ui(new Ui::GamerMenu), mainWindow(mainWin) {
    ui->setupUi(this);
    ui->deleteButton->setVisible(false);
}

GamerMenu::~GamerMenu() {
    delete ui;
}

QString formatGameGamer(const Game& game) {
    return QString("<b>Name:</b> %1<br><b>Genre:</b> %2<br><b>Version:</b> %3<br><b>Weight:</b> %4 Gb<br><b>Cost:</b> $%5<br><br>")
            .arg(QString::fromStdString(game.getName()))
            .arg(QString::fromStdString(game.getGenre()))
            .arg(QString::fromStdString(game.versionToString()))
            .arg(QString::number(game.getWeight()))
            .arg(QString::number(game.getCost()));
}

void GamerMenu::on_readLibraryButton_clicked() {
    QString gamesList;
    std::ifstream in("library.txt");
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    std::vector<Game> games;
    while (in.good()) {
        Game game = Game::readFromFile(in);
        if (in.good()) {
            games.push_back(game);
            gamesList += formatGameGamer(game);
        }
    }
    in.close();

    ui->outputTextArea->setHtml(gamesList);
}

void GamerMenu::on_findGameButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    std::ifstream in("library.txt");
    std::vector<Game> games;
    bool found = false;

    if (in.is_open()) {
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                games.push_back(game);
            }
        }
        in.close();
    } else {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    QString foundGameDetails;
    for (auto &game : games) {
        if (game.getName() == name.toStdString()) {
            found = true;
            foundGameDetails = formatGameGamer(game);
            ui->outputTextArea->setHtml(foundGameDetails);
            ui->deleteButton->setVisible(true);
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Not Found", "Invalid game name.");
        ui->outputTextArea->clear();
        ui->deleteButton->setVisible(false);
    }
}

void GamerMenu::on_deleteButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    deleteGameFromGamerFile(name.toStdString(), "library.txt");
    QMessageBox::information(this, "Success", "Game deleted successfully.");
    ui->deleteButton->setVisible(false);
    ui->outputTextArea->clear();
}

void GamerMenu::on_buyButton_clicked() {
    QString gameName = ui->gameNameInput->text().trimmed();

    if (gameName.isEmpty()) {
        QString gamesList;
        std::ifstream in("games.txt");
        if (!in.is_open()) {
            QMessageBox::critical(this, "Error", "Error opening games file.");
            return;
        }

        std::vector<Game> games;
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                games.push_back(game);
                gamesList += formatGameGamer(game);
            }
        }
        in.close();

        ui->outputTextArea->setHtml(gamesList);
        QMessageBox::information(this, "Available Games", "Please select a game from the list above.");
        return;
    }

    if (addGameToLibrary(gameName.toStdString())) {
        QMessageBox::information(this, "Success", "Game added to library.");
    } else {
        QString gamesList;
        std::ifstream in("games.txt");
        if (!in.is_open()) {
            QMessageBox::critical(this, "Error", "Error opening games file.");
            return;
        }

        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                gamesList += formatGameGamer(game);
            }
        }
        in.close();

        ui->outputTextArea->setHtml(gamesList);
        QMessageBox::warning(this, "Not Found", "Game not found. Please check the list above.");
    }
}

void GamerMenu::on_backButton_clicked() {
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}