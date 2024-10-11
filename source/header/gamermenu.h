#ifndef GAMERMENU_H
#define GAMERMENU_H

#include <QWidget>

class MainWindow;

namespace Ui {
    class GamerMenu;
}

class GamerMenu : public QWidget {
    Q_OBJECT

public:
    explicit GamerMenu(MainWindow *mainWin, QWidget *parent = nullptr);
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
};

#endif // GAMERMENU_H