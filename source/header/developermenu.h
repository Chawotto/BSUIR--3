#ifndef DEVELOPERMENU_H
#define DEVELOPERMENU_H

#include <QWidget>
#include <vector>
#include "Game.h"

class MainWindow;
class EnterWindow;

namespace Ui {
    class DeveloperMenu;
}

class DeveloperMenu : public QWidget {
    Q_OBJECT

public:
    explicit DeveloperMenu(MainWindow *mainWin,EnterWindow *enterWin, const QString &username, QWidget *parent = nullptr);
    ~DeveloperMenu() override;

    private slots:
        void on_createButton_clicked();
        void on_readGamesButton_clicked();
        void on_findButton_clicked();
        void on_backButton_clicked();
        void on_updateButton_clicked();
        void on_deleteButton_clicked();
        bool updateGameVersion(std::vector<Game> &games, const std::string_view &gameName);
        std::vector<Game> readGamesFromFile(std::ifstream &in);
        void updateGamesForAllUsers(const std::string &gameName);

private:
    Ui::DeveloperMenu *ui;
    MainWindow *mainWindow;
    EnterWindow *enterWindow;
    QString currentUser;
};

#endif // DEVELOPERMENU_H