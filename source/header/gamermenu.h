#ifndef GAMERMENU_H
#define GAMERMENU_H

#include <QWidget>
#include "Game.h"

class MainWindow;
class EnterWindow;

namespace Ui {
    class GamerMenu;
}

class GamerMenu : public QWidget {
    Q_OBJECT

public:
    explicit GamerMenu(MainWindow *mainWin, EnterWindow *enterWin, QString username, QWidget *parent = nullptr);
    ~GamerMenu() override;

    private slots:
    void on_gameListButton_clicked();
    void on_buyButton_clicked();
    void on_readLibraryButton_clicked();
    void on_findGameButton_clicked();
    void on_backButton_clicked();
    void on_deleteButton_clicked();

private:
    std::unique_ptr<Ui::GamerMenu> ui;
    MainWindow *mainWindow;
    EnterWindow *enterWindow;
    QString currentUser;
    std::vector<Game> foundGames;
};

#endif // GAMERMENU_H