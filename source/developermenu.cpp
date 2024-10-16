#include "ui_DeveloperMenu.h"
#include "header/devOpt.h"
#include <QMessageBox>
#include <QInputDialog>
#include <utility>
#include <fstream>
#include "header/Game.h"
#include "header/mainwindow.h"
#include <json/json.h>

DeveloperMenu::DeveloperMenu(MainWindow *mainWin, EnterWindow *enterWin, QString username, QWidget *parent) :
    QWidget(parent),
    ui(std::make_unique<Ui::DeveloperMenu>()),
    mainWindow(mainWin),
    enterWindow(enterWin),
    currentUser(std::move(username)) {
    ui->setupUi(this);
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);

    QPixmap background("C:/Users/alexe/Desktop/MorrsQT/source/Images/background.png");
    ui->backgroundLabel->setPixmap(background.scaled(ui->backgroundLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

DeveloperMenu::~DeveloperMenu() = default;

QString formatGame(const Game& game) {
    return QString("<b>Name:</b> %1<br><b>Genre:</b> %2<br><b>Version:</b> %3<br><b>Weight:</b> %4 Gb<br><b>Cost:</b> $%5<br><br>")
            .arg(QString::fromStdString(game.getName()))
            .arg(QString::fromStdString(game.getGenre()))
            .arg(QString::fromStdString(game.versionToString()))
            .arg(QString::number(game.getWeight()))
            .arg(QString::number(game.getCost()));
}

std::vector<QString> getGamerUsernames() {
    std::vector<QString> gamers;
    std::ifstream in("users.json");
    if (!in.is_open()) return gamers;

    Json::Value jsonData;
    in >> jsonData;

    for (const auto& user : jsonData) {
        QString username = QString::fromStdString(user["name"].asString());
        QString role = QString::fromStdString(user["role"].asString());

        if (role == "Gamer") {
            gamers.push_back(username);
        }
    }

    return gamers;
}

void saveGameToFile(const Game &game, const QString &fileName) {
    Json::Value jsonGame;
    jsonGame["name"] = game.getName();
    jsonGame["genre"] = game.getGenre();
    jsonGame["version"] = game.versionToString();
    jsonGame["weight"] = game.getWeight();
    jsonGame["cost"] = game.getCost();

    Json::Value jsonData;

    if (std::ifstream inFile(fileName.toStdString()); inFile.is_open()) {
        inFile >> jsonData;
        inFile.close();
    }

    jsonData.append(jsonGame);

    std::ofstream outFile(fileName.toStdString());
    Json::StreamWriterBuilder writer;
    outFile << Json::writeString(writer, jsonData);
}

void DeveloperMenu::on_createButton_clicked() {
    QString name = QInputDialog::getText(this, "Create Game", "Enter game name:");
    QString genre = QInputDialog::getText(this, "Create Game", "Enter game genre:");
    if (name.isEmpty() || genre.isEmpty()) return;

    QComboBox versionComboBox;
    versionComboBox.addItem("Pre Alpha");
    versionComboBox.addItem("Alpha");
    versionComboBox.addItem("Beta");
    versionComboBox.addItem("Release Candidate");
    versionComboBox.addItem("General Availability");

    bool ok;
    QStringList items;
    for (int i = 0; i < versionComboBox.count(); ++i) {
        items << versionComboBox.itemText(i);
    }
    QString selectedItem = QInputDialog::getItem(this, "Select Game Version", "Select game version:", items, 0, false, &ok);
    if (!ok) return;

    int versionIndex = versionComboBox.findText(selectedItem);
    auto selectedVersion = static_cast<versions>(versionIndex);

    double weight = QInputDialog::getDouble(this, "Create Game", "Enter game weight (Gb):", 0.0, 0.0, 100.0, 1, &ok);
    if (!ok) return;
    double cost = QInputDialog::getDouble(this, "Create Game", "Enter game cost ($):", 0.0, 0.0, 1000.0, 1, &ok);
    if (!ok) return;

    Game game(name.toStdString(), genre.toStdString(), selectedVersion, static_cast<float>(weight), static_cast<float>(cost));

    saveGameToFile(game, "games.json");
    saveGameToFile(game, currentUser + ".json");

    QMessageBox::information(this, "Success", "Game information saved to both files.");
}

std::vector<Game> readGamesFromFile(const std::string& fileName) {
    std::vector<Game> games;
    std::ifstream in(fileName);
    if (!in.is_open()) return games;

    Json::Value jsonData;
    in >> jsonData;

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
    }

    return games;
}

void DeveloperMenu::on_readGamesButton_clicked() {
    QString gamesList;
    QString userFileName = currentUser + ".json";

    std::vector<Game> readGamesFromFile(const std::string& fileName);
    std::vector<Game> games = readGamesFromFile(userFileName.toStdString());

    for (const auto &game : games) {
        gamesList += formatGame(game);
    }

    ui->outputTextArea->setHtml(gamesList);
}

void DeveloperMenu::on_findButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".json";

    std::vector<Game> readGamesFromFile(const std::string& fileName);
    std::vector<Game> games = readGamesFromFile(userFileName.toStdString());

    auto it = std::ranges::find_if(games, [&](const Game &game) { return game.getName() == name.toStdString(); });

    if (it != games.end()) {
        ui->outputTextArea->setHtml(formatGame(*it));
        ui->versionComboBox->setVisible(true);
        ui->deleteButton->setVisible(true);
        ui->updateButton->setVisible(true);
    } else {
        QMessageBox::warning(this, "Not Found", "Invalid game name.");
        ui->outputTextArea->clear();
        ui->versionComboBox->setVisible(false);
        ui->deleteButton->setVisible(false);
        ui->updateButton->setVisible(false);
    }
}

void deleteGameFromFile(const std::string &gameName, const QString &fileName) {
    std::vector<Game> games = readGamesFromFile(fileName.toStdString());
    std::erase_if(games, [&gameName](const Game &game) {
        return game.getName() == gameName;
    });

    Json::Value jsonData;
    for (const auto &game : games) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();
        jsonGame["version"] = game.versionToString();
        jsonGame["weight"] = game.getWeight();
        jsonGame["cost"] = game.getCost();
        jsonData.append(jsonGame);
    }

    std::ofstream outFile(fileName.toStdString());
    outFile << jsonData;
}

void DeveloperMenu::on_deleteButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".json";

    deleteGameFromFile(name.toStdString(), userFileName);
    deleteGameFromFile(name.toStdString(), "games.json");

    std::vector<QString> gamerUsernames = getGamerUsernames();

    for (const auto& gamerUsername : gamerUsernames) {
        QString gamerFileName = gamerUsername + ".json";
        deleteGameFromFile(name.toStdString(), gamerFileName);
    }

    QMessageBox::information(this, "Success", "Game deleted successfully from all relevant files.");
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
}

void saveGamesToFile(const std::vector<Game> &games, const QString &fileName) {
    Json::Value jsonData;
    for (const auto &game : games) {
        Json::Value jsonGame;
        jsonGame["name"] = game.getName();
        jsonGame["genre"] = game.getGenre();
        jsonGame["version"] = game.versionToString();
        jsonGame["weight"] = game.getWeight();
        jsonGame["cost"] = game.getCost();
        jsonData.append(jsonGame);
    }

    std::ofstream outFile(fileName.toStdString());
    outFile << jsonData;
}

void DeveloperMenu::on_updateButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".json";
    std::vector<Game> userGames = readGamesFromFile(userFileName.toStdString());

    bool gameUpdated = updateGameVersion(userGames, name.toStdString());

    if (gameUpdated) {
        saveGamesToFile(userGames, userFileName);

        std::vector<Game> allGames = readGamesFromFile("games.json");
        if (updateGameVersion(allGames, name.toStdString())) {
            saveGamesToFile(allGames, "games.json");
        }

        std::vector<QString> gamerUsernames = getGamerUsernames();

        for (const auto& gamerUsername : gamerUsernames) {
            QString gamerFileName = gamerUsername + ".json";
            std::vector<Game> gamerGames = readGamesFromFile(gamerFileName.toStdString());

            if (updateGameVersion(gamerGames, name.toStdString())) {
                saveGamesToFile(gamerGames, gamerFileName);
            }
        }

        QMessageBox::information(this, "Success", "Game updated successfully in all relevant files.");
    } else {
        QMessageBox::warning(this, "Not Found", "Game not found.");
    }

    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
}

bool DeveloperMenu::updateGameVersion(std::vector<Game> &games, const std::string_view &gameName) {
    for (auto &game : games) {
        if (game.getName() == gameName) {
            int selectedIndex = ui->versionComboBox->currentIndex();
            game.updateVersion(static_cast<versions>(selectedIndex));
            return true;
        }
    }
    return false;
}


void DeveloperMenu::on_backButton_clicked() {
    ui->outputTextArea->clear();
    ui->gameNameInput->clear();
    ui->versionComboBox->setVisible(false);
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);

    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}
