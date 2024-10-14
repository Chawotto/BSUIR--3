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
    bool validateUser(const QString &username, const QString &password);
    void openUserMenu(const QString &userRole, const QString &username);

private:
    std::unique_ptr<Ui::EnterWindow> ui;
    DeveloperMenu *developerMenu = nullptr;
    GamerMenu *gamerMenu = nullptr;
    MainWindow *mainWindow;
    std::unique_ptr<QWidget> menu;
};

#endif // ENTERWINDOW_H