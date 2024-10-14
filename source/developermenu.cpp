#include "ui_DeveloperMenu.h"
#include "header/devOpt.h"
#include <QMessageBox>
#include <QInputDialog>
#include <utility>
#include "header/Game.h"
#include "header/mainwindow.h"

DeveloperMenu::DeveloperMenu(MainWindow *mainWin, EnterWindow *enterWin, QString username, QWidget *parent) :
    QWidget(parent), ui(new Ui::DeveloperMenu()), mainWindow(mainWin), enterWindow(enterWin),
    currentUser(std::move(username)) {
    ui->setupUi(this);
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
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
    std::ifstream in("users.txt");
    if (!in.is_open()) return gamers;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        QString username;
        QString role;
        std::string temp;

        if (!std::getline(iss, temp, ',')) continue;
        username = QString::fromStdString(temp);

        for (int i = 0; i < 4; ++i) std::getline(iss, temp, ',');

        if (std::getline(iss, temp, ',') && QString::fromStdString(temp) == "Gamer") {
            gamers.push_back(username);
        }
    }

    return gamers;
}

void saveGameToFile(const Game &game, const QString &fileName) {
    std::ofstream outFile(fileName.toStdString(), std::ios::app);
    if (outFile.is_open()) {
        game.saveToFile(outFile);
        outFile.close();
    }
}

void DeveloperMenu::on_createButton_clicked() {
    QString name = QInputDialog::getText(this, "Create Game", "Enter game name:");
    QString genre = QInputDialog::getText(this, "Create Game", "Enter game genre:");
    bool ok;
    int versionInt = QInputDialog::getInt(this, "Create Game", "Enter game version (0-4):", 0, 0, 4, 1, &ok);
    if (!ok) return;
    double weight = QInputDialog::getDouble(this, "Create Game", "Enter game weight (Gb):", 0.0, 0.0, 100.0, 1, &ok);
    if (!ok) return;
    double cost = QInputDialog::getDouble(this, "Create Game", "Enter game cost ($):", 0.0, 0.0, 1000.0, 1, &ok);
    if (!ok) return;

    Game game(name.toStdString(), genre.toStdString(), static_cast<versions>(versionInt), static_cast<float>(weight), static_cast<float>(cost));

    saveGameToFile(game, "games.txt");
    saveGameToFile(game, currentUser + ".txt");

    QMessageBox::information(this, "Success", "Game information saved to both files.");
}

void DeveloperMenu::on_readGamesButton_clicked() {
    QString gamesList;
    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    std::vector<Game> games = readGamesFromFile(in);
    in.close();

    for (const auto &game : games) {
        gamesList += formatGame(game);
    }

    ui->outputTextArea->setHtml(gamesList);
}

std::vector<Game> DeveloperMenu::readGamesFromFile(std::ifstream &in) {
    std::vector<Game> games;
    while (in.good()) {
        Game game = Game::readFromFile(in);
        if (in.good()) {
            games.push_back(game);
        }
    }
    return games;
}

void DeveloperMenu::on_findButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    std::vector<Game> games = readGamesFromFile(in);
    in.close();

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

void deleteGameFromAllUsers(const std::string &gameName) {
    std::vector<QString> gamers = getGamerUsernames();
    for (const auto &gamer : gamers) {
        QString gamerFileName = gamer + ".txt";
        deleteGameFromFile(gameName, gamerFileName.toStdString());
    }
}

void DeveloperMenu::on_deleteButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".txt";
    deleteGameFromFile(name.toStdString(), userFileName.toStdString());
    deleteGameFromFile(name.toStdString(), "games.txt");
    deleteGameFromAllUsers(name.toStdString());

    QMessageBox::information(this, "Success", "Game deleted successfully.");
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
}

void saveGamesToFile(const std::vector<Game> &games, const QString &fileName) {
    std::ofstream outFile(fileName.toStdString());
    if (outFile.is_open()) {
        for (const auto &game : games) {
            game.saveToFile(outFile);
        }
        outFile.close();
    }
}

void DeveloperMenu::updateGamesForAllUsers(const std::string &gameName) {
    std::vector<QString> gamers = getGamerUsernames();
    for (const auto &gamer : gamers) {
        QString gamerFileName = gamer + ".txt";
        std::ifstream inGamer(gamerFileName.toStdString());
        if (!inGamer.is_open()) continue;

        std::vector<Game> gamerGames = readGamesFromFile(inGamer);
        inGamer.close();

        this->updateGameVersion(gamerGames, gameName);

        saveGamesToFile(gamerGames, gamerFileName);
    }
}


void DeveloperMenu::on_updateButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    std::vector<Game> userGames = readGamesFromFile(in);
    in.close();

    bool gameUpdated = updateGameVersion(userGames, name.toStdString());
    if (gameUpdated) {
        saveGamesToFile(userGames, userFileName);

        updateGamesForAllUsers(name.toStdString());

        QMessageBox::information(this, "Success", "Game updated successfully.");
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
