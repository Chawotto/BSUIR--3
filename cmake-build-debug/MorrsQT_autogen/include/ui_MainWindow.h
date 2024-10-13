/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *signInButton;
    QPushButton *signUpButton;
    QPushButton *exitButton;
    QTextEdit *outputTextArea;
    QStatusBar *statusbar;
    QLabel *logoLabel;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(851, 551);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(240, 220, 400, 300));
        signInButton = new QPushButton(centralwidget);
        signInButton->setObjectName("signInButton");
        signInButton->setGeometry(QRect(110, 20, 151, 61));
        signInButton->setTabletTracking(false);
        signInButton->setStyleSheet(QString::fromUtf8("\n"
"      QPushButton {\n"
"          background-color: #3498DB;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #2980B9;\n"
"      }\n"
"     "));
        signUpButton = new QPushButton(centralwidget);
        signUpButton->setObjectName("signUpButton");
        signUpButton->setGeometry(QRect(110, 100, 151, 61));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(110, 180, 151, 61));
        outputTextArea = new QTextEdit(centralwidget);
        outputTextArea->setObjectName("outputTextArea");
        outputTextArea->setGeometry(QRect(50, 300, 500, 150));
        outputTextArea->setReadOnly(true);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 21));
        logoLabel = new QLabel(MainWindow);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(340, 50, 161, 161));
        logoLabel->setStyleSheet(QString::fromUtf8("  QPushButton {\n"
"          border-radius: 20px;\n"
"      }"));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("Images/logo.png")));
        logoLabel->setScaledContents(true);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MorrS", nullptr));
        signInButton->setText(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        signUpButton->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"      QPushButton {\n"
"          background-color: #E74C3C;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #C0392B;\n"
"      }\n"
"     ", nullptr));
        signUpButton->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        exitButton->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"      QPushButton {\n"
"          background-color: #1ABC9C;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #16A085;\n"
"      }\n"
"     ", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
