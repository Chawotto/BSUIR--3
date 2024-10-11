#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>

#include "developermenu.h"
#include "gamermenu.h"

namespace Ui {
    class DeveloperMenu;
    class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        void on_developerButton_clicked();
    void on_gamerButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    DeveloperMenu *developerMenu = nullptr;
    GamerMenu *gamerMenu = nullptr;

    QLabel *logoLabel;
};

#endif // MAINWINDOW_H