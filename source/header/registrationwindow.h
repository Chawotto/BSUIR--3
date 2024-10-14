#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "User.h"
#include <QWidget>

class MainWindow;

namespace Ui {
    class RegistrationWindow;
}


class RegistrationWindow : public QWidget {
    Q_OBJECT

public:
    explicit RegistrationWindow(MainWindow *mainWin, QWidget *parent = nullptr);
    ~RegistrationWindow() override;

    void clearInputs();

    private slots:
        void saveUser();
        static userRole roleToEnum(const QString &role);
        void on_backButton_clicked();

private:
    std::unique_ptr<Ui::RegistrationWindow> ui;
    MainWindow *mainWindow;

};

#endif // REGISTRATIONWINDOW_H