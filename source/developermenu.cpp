#include "ui_DeveloperMenu.h"
#include "header/devOpt.h"
#include <QMessageBox>
#include <QInputDialog>
#include "header/Game.h"
#include "header/mainwindow.h"

DeveloperMenu::DeveloperMenu(MainWindow *mainWin, QWidget *parent) :
    QWidget(parent), ui(new Ui::DeveloperMenu), mainWindow(mainWin) {
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

    std::ofstream out("games.txt", std::ios::app);
    if (out.is_open()) {
        game.saveToFile(out);
        out.close();
        QMessageBox::information(this, "Success", "Game information saved to file.");
    } else {
        QMessageBox::critical(this, "Error", "Error opening file for writing.");
    }
}

void DeveloperMenu::on_readGamesButton_clicked() {
    QString gamesList;
    std::ifstream in("games.txt");
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

    std::ifstream in("games.txt");
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
            ui->versionComboBox->setVisible(true); // Показать QComboBox
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

    deleteGameFromFile(name.toStdString(), "games.txt");
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

    std::ifstream in("games.txt");
    std::vector<Game> games;

    if (in.is_open()) {
        while (in.good()) {
            Game game = Game::readFromFile(in);
            if (in.good()) {
                games.push_back(game);
            }
        }
        in.close();
    }

    for (auto &game : games) {
        if (game.getName() == name.toStdString()) {
            // Получаем выбранную версию из QComboBox
            int selectedIndex = ui->versionComboBox->currentIndex();
            game.updateVersion(static_cast<versions>(selectedIndex)); // Обновление версии
            updateGameInFile(games, "games.txt");
            QMessageBox::information(this, "Success", "Game updated successfully.");
            break;
        }
    }

    ui->deleteButton->setVisible(false);
    ui->updateButton->setVisible(false);
    ui->outputTextArea->clear();
}

void DeveloperMenu::on_backButton_clicked() {
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}