#ifndef GAMERMENU_H
#define GAMERMENU_H

#include <QWidget>

class MainWindow;
class EnterWindow;

namespace Ui {
    class GamerMenu;
}

class GamerMenu : public QWidget {
    Q_OBJECT

public:
    explicit GamerMenu(MainWindow *mainWin, EnterWindow *enterWin, const QString &username, QWidget *parent = nullptr);
    ~GamerMenu() override;

    private slots:
        void on_buyButton_clicked();
    void on_readLibraryButton_clicked();
    void on_findGameButton_clicked();
    void on_backButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::GamerMenu *ui;
    MainWindow *mainWindow;
    EnterWindow *enterWindow;
    QString currentUser;
};

#endif // GAMERMENU_H