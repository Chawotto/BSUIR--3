#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include "registrationwindow.h"
#include "enterwindow.h"
#include <memory>

namespace Ui {
    class DeveloperMenu;
    class RegistrationWindow;
    class GamerMenu;
    class EnterWindow;
    class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
    void on_signInButton_clicked();
    void on_signUpButton_clicked();
    void on_exitButton_clicked();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<EnterWindow> enterWindow;
    std::unique_ptr<RegistrationWindow> registrationWindow;
    QLabel *logoLabel{};
};

#endif // MAINWINDOW_H