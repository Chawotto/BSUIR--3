/********************************************************************************
** Form generated from reading UI file 'gamermenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMERMENU_H
#define UI_GAMERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GamerMenu
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QLineEdit *gameNameInput;
    QPushButton *buyButton;
    QPushButton *findGameButton;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QPushButton *readLibraryButton;
    QStatusBar *statusbar;
    QTextEdit *outputTextArea;

    void setupUi(QWidget *GamerMenu)
    {
        if (GamerMenu->objectName().isEmpty())
            GamerMenu->setObjectName("GamerMenu");
        GamerMenu->resize(724, 540);
        GamerMenu->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(GamerMenu);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(30, 20, 600, 400));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(210, 0, 200, 40));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gameNameInput = new QLineEdit(centralwidget);
        gameNameInput->setObjectName("gameNameInput");
        gameNameInput->setGeometry(QRect(70, 60, 500, 30));
        gameNameInput->setStyleSheet(QString::fromUtf8("  QPushButton {\n"
"          border-radius: 50px;\n"
"         \n"
"      }"));
        buyButton = new QPushButton(centralwidget);
        buyButton->setObjectName("buyButton");
        buyButton->setGeometry(QRect(70, 100, 201, 61));
        findGameButton = new QPushButton(centralwidget);
        findGameButton->setObjectName("findGameButton");
        findGameButton->setGeometry(QRect(320, 170, 201, 61));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(70, 170, 201, 61));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(200, 250, 201, 61));
        readLibraryButton = new QPushButton(centralwidget);
        readLibraryButton->setObjectName("readLibraryButton");
        readLibraryButton->setGeometry(QRect(320, 100, 201, 61));
        statusbar = new QStatusBar(GamerMenu);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 21));
        outputTextArea = new QTextEdit(GamerMenu);
        outputTextArea->setObjectName("outputTextArea");
        outputTextArea->setGeometry(QRect(30, 340, 661, 181));
        outputTextArea->setReadOnly(true);

        retranslateUi(GamerMenu);

        QMetaObject::connectSlotsByName(GamerMenu);
    } // setupUi

    void retranslateUi(QWidget *GamerMenu)
    {
        GamerMenu->setWindowTitle(QCoreApplication::translate("GamerMenu", "Game Library", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
"      font-size: 24px;\n"
"      font-weight: bold;\n"
"      color: #2C3E50;\n"
"     ", nullptr));
        titleLabel->setText(QCoreApplication::translate("GamerMenu", "Game Library", nullptr));
        gameNameInput->setPlaceholderText(QCoreApplication::translate("GamerMenu", "Enter game name", nullptr));
        buyButton->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
"      QPushButton {\n"
"          background-color: #3498DB;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #2980B9;\n"
"      }\n"
"     ", nullptr));
        buyButton->setText(QCoreApplication::translate("GamerMenu", "Buy Game", nullptr));
        findGameButton->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
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
        findGameButton->setText(QCoreApplication::translate("GamerMenu", "Find Game", nullptr));
        backButton->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
"      QPushButton {\n"
"          background-color: #F39C12;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #E67E22;\n"
"      }\n"
"     ", nullptr));
        backButton->setText(QCoreApplication::translate("GamerMenu", "Back", nullptr));
        deleteButton->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
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
        deleteButton->setText(QCoreApplication::translate("GamerMenu", "Delete Game", nullptr));
        readLibraryButton->setStyleSheet(QCoreApplication::translate("GamerMenu", "\n"
"      QPushButton {\n"
"          background-color: #8E44AD;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #732D91;\n"
"      }\n"
"     ", nullptr));
        readLibraryButton->setText(QCoreApplication::translate("GamerMenu", "Read Library", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GamerMenu: public Ui_GamerMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMERMENU_H
