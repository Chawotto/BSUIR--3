#include "header/gamermenu.h"
#include "ui_GamerMenu.h"
#include "header/gamOpt.h"
#include "header/Game.h"
#include <QMessageBox>
#include <QInputDialog>
#include "header/mainwindow.h"
#include <fstream>
#include <utility>
#include <vector>
#include <json/json.h>

GamerMenu::GamerMenu(MainWindow *mainWin, EnterWindow *enterWin, QString username, QWidget *parent) :
    QWidget(parent),
    ui(std::make_unique<Ui::GamerMenu>()),
    mainWindow(mainWin),
    enterWindow(enterWin),
    currentUser(std::move(username)) {
    ui->setupUi(this);
    ui->deleteButton->setVisible(false);

    QPixmap background("C:/Users/alexe/Desktop/MorrsQT/source/Images/background.png");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

GamerMenu::~GamerMenu() = default;

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
    QString userFileName = currentUser + ".json";
    std::ifstream in(userFileName.toStdString());

    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    Json::Value jsonData;
    in >> jsonData;
    in.close();

    if (jsonData.empty()) {
        QMessageBox::information(this, "Library Empty", "No games found in your library.");
        return;
    }

    std::vector<Game> games;
    for (const auto& jsonGame : jsonData) {
        using enum versions;
        std::string name = jsonGame["name"].asString();
        std::string genre = jsonGame["genre"].asString();
        std::string versionStr = jsonGame["version"].asString();
        float weight = jsonGame["weight"].asFloat();
        float cost = jsonGame["cost"].asFloat();

        versions version;
        if (versionStr == "Pre_Alpha") {
            version = Pre_Alpha;
        } else if (versionStr == "Alfa") {
            version = Alfa;
        } else if (versionStr == "Beta") {
            version = Beta;
        } else if (versionStr == "Release_Candidate") {
            version = Release_Candidate;
        } else if (versionStr == "General_Availability") {
            version = General_Availability;
        } else {
            continue;
        }

        Game game(name, genre, version, weight, cost);
        games.push_back(game);

        gamesList += formatGameGamer(game);
    }

    if (gamesList.isEmpty()) {
        QMessageBox::information(this, "Library Empty", "No valid games found in your library.");
    } else {
        ui->outputTextArea->setHtml(gamesList);
    }
}

void GamerMenu::on_findGameButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".json";
    std::ifstream in(userFileName.toStdString());
    std::vector<Game> games;
    bool found = false;

    if (in.is_open()) {
        Json::Value jsonData;
        in >> jsonData;

        for (const auto& jsonGame : jsonData) {
            using enum versions;
            std::string versionStr = jsonGame["version"].asString();

            versions version;
            if (versionStr == "Pre_Alpha") {
                version = Pre_Alpha;
            } else if (versionStr == "Alfa") {
                version = Alfa;
            } else if (versionStr == "Beta") {
                version = Beta;
            } else if (versionStr == "Release_Candidate") {
                version = Release_Candidate;
            } else if (versionStr == "General_Availability") {
                version = General_Availability;
            } else {
                continue;
            }

            Game game(
                jsonGame["name"].asString(),
                jsonGame["genre"].asString(),
                version,
                jsonGame["weight"].asFloat(),
                jsonGame["cost"].asFloat()
            );
            games.push_back(game);
        }
        in.close();
    } else {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    QString foundGamesList;
    std::vector<Game> foundGames; // Вектор для хранения найденных игр
    for (const auto &game : games) {
        if (game.getName().contains(name.toStdString())) {
            found = true;
            QString foundGameDetails = formatGameGamer(game);
            foundGamesList += foundGameDetails;
            foundGames.push_back(game); // Добавляем найденную игру в вектор
        }
    }

    if (found) {
        ui->outputTextArea->setHtml(foundGamesList);
        ui->deleteButton->setVisible(true);
        ui->gameListButton->setVisible(true); // Показываем кнопку gameList
        // Сохраняем найденные игры в атрибут класса, если нужно
        this->foundGames = foundGames; // Предполагается, что вы добавили атрибут foundGames в класс
    } else {
        QMessageBox::warning(this, "Not Found", "No games found with the specified name.");
        ui->outputTextArea->clear();
        ui->deleteButton->setVisible(false);
        ui->gameListButton->setVisible(false); // Скрываем кнопку gameList
    }
}

void GamerMenu::on_gameListButton_clicked() {
    QString userFileName = currentUser + "_foundGames.json";
    Json::Value jsonData;

    for (const auto &game : foundGames) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();
        jsonGame["version"] = game.versionToString();
        jsonGame["weight"] = game.getWeight();
        jsonGame["cost"] = game.getCost();

        jsonData.append(jsonGame);
    }

    std::ofstream out(userFileName.toStdString());
    if (!out.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for writing.");
        return;
    }
    out << jsonData;
    out.close();

    QMessageBox::information(this, "Success", "Game list saved successfully as " + userFileName);
}

void GamerMenu::on_deleteButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".json";
    deleteGameFromGamerFile(name.toStdString(), userFileName.toStdString());
    QMessageBox::information(this, "Success", "Game deleted successfully.");
    ui->deleteButton->setVisible(false);
    ui->outputTextArea->clear();
}

void GamerMenu::on_buyButton_clicked() {
    QString gameName = ui->gameNameInput->text().trimmed();
    QString userFileName = currentUser + ".json";

    if (gameName.isEmpty()) {
        QString gamesList;
        std::ifstream in("games.json");
        if (!in.is_open()) {
            QMessageBox::critical(this, "Error", "Error opening games file.");
            return;
        }

        Json::Value jsonData;
        in >> jsonData;
        in.close();

        std::vector<Game> games;
        for (const auto& jsonGame : jsonData) {
            using enum versions;
            std::string versionStr = jsonGame["version"].asString();

            versions version;
            if (versionStr == "Pre_Alpha") {
                version = Pre_Alpha;
            } else if (versionStr == "Alfa") {
                version = Alfa;
            } else if (versionStr == "Beta") {
                version = Beta;
            } else if (versionStr == "Release_Candidate") {
                version = Release_Candidate;
            } else if (versionStr == "General_Availability") {
                version = General_Availability;
            } else {
                continue;
            }

            Game game(
                jsonGame["name"].asString(),
                jsonGame["genre"].asString(),
                version,
                jsonGame["weight"].asFloat(),
                jsonGame["cost"].asFloat()
            );
            games.push_back(game);

            gamesList += formatGameGamer(game);
        }

        ui->outputTextArea->setHtml(gamesList);
        QMessageBox::information(this, "Available Games", "Please select a game from the list above.");
        return;
    }

    std::ifstream in("games.json");
    Json::Value jsonData;
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening games file.");
        return;
    }

    in >> jsonData;
    in.close();

    bool foundGame = false;
    for (const auto& jsonGame : jsonData) {
        if (jsonGame["name"].asString() == gameName.toStdString()) {
            foundGame = true;
            break;
        }
    }

    if (!foundGame) {
        QMessageBox::warning(this, "Not Found", "Game not found in available games. Please check the name.");
        return;
    }

    std::ifstream inFile(userFileName.toStdString());
    Json::Value userGamesData;
    if (inFile.is_open()) {
        inFile >> userGamesData;
        inFile.close();
    }

    bool gameExists = false;
    for (const auto& jsonGame : userGamesData) {
        if (jsonGame["name"].asString() == gameName.toStdString()) {
            gameExists = true;
            break;
        }
    }

    if (gameExists) {
        QMessageBox::information(this, "Error", "Game is already in your library.");
        return;
    }

    if (addGameToLibrary(gameName.toStdString(), userFileName.toStdString())) {
        QMessageBox::information(this, "Success", "Game added to library.");
    } else {
        QMessageBox::warning(this, "Not Found", "Game not found. Please check the list above.");
    }
}

void GamerMenu::on_backButton_clicked() {
    ui->outputTextArea->clear();
    ui->gameNameInput->clear();
    ui->deleteButton->setVisible(false);

    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}