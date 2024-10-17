#ifndef DEVELOPERMENU_H
#define DEVELOPERMENU_H

#include <QWidget>
#include <vector>
#include <memory>
#include "Game.h"
#include "gamecollection.h"

class MainWindow;
class EnterWindow;

namespace Ui {
    class DeveloperMenu;
}

class DeveloperMenu : public QWidget {
    Q_OBJECT

public:
    explicit DeveloperMenu(MainWindow *mainWin, EnterWindow *enterWin, QString username, QWidget *parent = nullptr);
    ~DeveloperMenu() override;

    private slots:
    void on_createButton_clicked();
    void on_readGamesButton_clicked();
    void on_findButton_clicked();
    void on_backButton_clicked();
    void on_updateButton_clicked();
    void on_deleteButton_clicked();
    bool updateGameVersion(std::vector<Game> &games, const std::string_view &gameName) const;

private:
    std::unique_ptr<Ui::DeveloperMenu> ui;
    MainWindow *mainWindow;
    EnterWindow *enterWindow;
    QString currentUser;
    GameCollection gameCollection;
};

#endif // DEVELOPERMENU_H