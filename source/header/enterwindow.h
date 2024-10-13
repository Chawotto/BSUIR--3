#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include "developermenu.h"
#include "gamermenu.h"

class MainWindow;

namespace Ui {
    class EnterWindow;
    class DeveloperMenu;
    class GamerMenu;
}

class EnterWindow : public QWidget {
    Q_OBJECT

public:
    explicit EnterWindow(MainWindow *mainWin, QWidget *parent = nullptr);
    ~EnterWindow() override;

    void clearInputs() const;

    private slots:
        void on_loginButton_clicked();
        void on_backButton_clicked();

private:
    Ui::EnterWindow *ui;
    DeveloperMenu *developerMenu = nullptr;
    GamerMenu *gamerMenu = nullptr;
    MainWindow *mainWindow;
};

#endif // ENTERWINDOW_H