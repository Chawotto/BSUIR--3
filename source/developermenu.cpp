#include "ui_DeveloperMenu.h"
#include "header/devOpt.h"
#include <QMessageBox>
#include <QInputDialog>
#include "header/Game.h"
#include "header/mainwindow.h"

DeveloperMenu::DeveloperMenu(MainWindow *mainWin, EnterWindow *enterWin, const QString &username, QWidget *parent) :
    QWidget(parent), ui(new Ui::DeveloperMenu), mainWindow(mainWin), enterWindow(enterWin), currentUser(username) {
    ui->setupUi(this);
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
}

DeveloperMenu::~DeveloperMenu() {
    delete ui;
}

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
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            QString username;
            QString role;
            std::string temp;

            std::getline(iss, temp, ',');
            username = QString::fromStdString(temp);
            for (int i = 0; i < 4; ++i) std::getline(iss, temp, ',');
            std::getline(iss, temp, ',');
            role = QString::fromStdString(temp);

            if (role == "Gamer") {
                gamers.push_back(username);
            }
        }
        in.close();
    }
    return gamers;
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

    QString userFileName = currentUser + ".txt";
    std::ofstream outGames("games.txt", std::ios::app);
    std::ofstream outUser(userFileName.toStdString(), std::ios::app);

    if (outGames.is_open() && outUser.is_open()) {
        game.saveToFile(outGames);
        game.saveToFile(outUser);
        QMessageBox::information(this, "Success", "Game information saved to both files.");
    } else {
        QMessageBox::critical(this, "Error", "Error opening file for writing.");
    }

    outGames.close();
    outUser.close();
}

void DeveloperMenu::on_readGamesButton_clicked() {
    QString gamesList;
    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
    if (!in.is_open()) {
        QMessageBox::critical(this, "Error", "Error opening file for reading.");
        return;
    }

    std::vector<Game> games;
    while (in.good()) {
        Game game = Game::readFromFile(in);
        if (in.good()) {
            games.push_back(game);
            gamesList += formatGame(game);
        }
    }
    in.close();

    ui->outputTextArea->setHtml(gamesList);
}

void DeveloperMenu::on_findButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
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
            foundGameDetails = formatGame(game);
            ui->outputTextArea->setHtml(foundGameDetails);
            ui->versionComboBox->setVisible(true);
            ui->deleteButton->setVisible(true);
            ui->updateButton->setVisible(true);
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Not Found", "Invalid game name.");
        ui->outputTextArea->clear();
        ui->versionComboBox->setVisible(false);
        ui->deleteButton->setVisible(false);
        ui->updateButton->setVisible(false);
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

    std::vector<QString> gamers = getGamerUsernames();
    for (const auto& gamer : gamers) {
        QString gamerFileName = gamer + ".txt";
        deleteGameFromFile(name.toStdString(), gamerFileName.toStdString());
    }

    QMessageBox::information(this, "Success", "Game deleted successfully.");
    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
}

void DeveloperMenu::on_updateButton_clicked() {
    QString name = ui->gameNameInput->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Game name cannot be empty.");
        return;
    }

    QString userFileName = currentUser + ".txt";
    std::ifstream in(userFileName.toStdString());
    std::vector<Game> userGames;

    if (in.is_open()) {
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                userGames.push_back(game);
            }
        }
        in.close();
    }

    bool gameUpdated = false;
    for (auto &game : userGames) {
        if (game.getName() == name.toStdString()) {
            int selectedIndex = ui->versionComboBox->currentIndex();
            game.updateVersion(static_cast<versions>(selectedIndex));
            gameUpdated = true;
            break;
        }
    }

    if (gameUpdated) {
        std::ofstream outUser(userFileName.toStdString());
        if (outUser.is_open()) {
            for (const auto &game : userGames) {
                game.saveToFile(outUser);
            }
            outUser.close();
        } else {
            QMessageBox::critical(this, "Error", "Error opening user file for writing.");
        }

        std::vector<QString> gamers = getGamerUsernames();
        for (const auto& gamer : gamers) {
            QString gamerFileName = gamer + ".txt";
            std::ifstream inGamer(gamerFileName.toStdString());
            std::vector<Game> gamerGames;

            if (inGamer.is_open()) {
                while (inGamer.good()) {
                    Game game = Game::readFromFile(inGamer);
                    if (inGamer.good()) {
                        gamerGames.push_back(game);
                    }
                }
                inGamer.close();
            }

            for (auto &game : gamerGames) {
                if (game.getName() == name.toStdString()) {
                    int selectedIndex = ui->versionComboBox->currentIndex();
                    game.updateVersion(static_cast<versions>(selectedIndex));
                    break;
                }
            }

            std::ofstream outGamer(gamerFileName.toStdString());
            if (outGamer.is_open()) {
                for (const auto &game : gamerGames) {
                    game.saveToFile(outGamer);
                }
                outGamer.close();
            }
        }

        QMessageBox::information(this, "Success", "Game updated successfully.");
    }

    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
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