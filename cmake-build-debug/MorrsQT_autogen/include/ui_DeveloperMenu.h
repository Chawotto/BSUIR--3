/********************************************************************************
** Form generated from reading UI file 'developermenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVELOPERMENU_H
#define UI_DEVELOPERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeveloperMenu
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QLineEdit *gameNameInput;
    QComboBox *versionComboBox;
    QPushButton *createButton;
    QPushButton *findButton;
    QPushButton *readGamesButton;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QStatusBar *statusbar;
    QTextEdit *outputTextArea;

    void setupUi(QWidget *DeveloperMenu)
    {
        if (DeveloperMenu->objectName().isEmpty())
            DeveloperMenu->setObjectName("DeveloperMenu");
        DeveloperMenu->resize(724, 624);
        centralwidget = new QWidget(DeveloperMenu);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 600, 400));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(250, 20, 211, 40));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gameNameInput = new QLineEdit(centralwidget);
        gameNameInput->setObjectName("gameNameInput");
        gameNameInput->setGeometry(QRect(110, 80, 500, 30));
        gameNameInput->setStyleSheet(QString::fromUtf8("  QPushButton {\n"
"         \n"
"         \n"
"          border-radius: 50px;\n"
"         \n"
"      }"));
        versionComboBox = new QComboBox(centralwidget);
        versionComboBox->addItem(QString());
        versionComboBox->addItem(QString());
        versionComboBox->addItem(QString());
        versionComboBox->addItem(QString());
        versionComboBox->addItem(QString());
        versionComboBox->setObjectName("versionComboBox");
        versionComboBox->setGeometry(QRect(110, 120, 500, 30));
        versionComboBox->setVisible(false);
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(120, 160, 201, 61));
        findButton = new QPushButton(centralwidget);
        findButton->setObjectName("findButton");
        findButton->setGeometry(QRect(390, 160, 201, 61));
        readGamesButton = new QPushButton(centralwidget);
        readGamesButton->setObjectName("readGamesButton");
        readGamesButton->setGeometry(QRect(390, 230, 201, 61));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(120, 230, 201, 61));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(120, 310, 201, 61));
        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName("updateButton");
        updateButton->setGeometry(QRect(390, 310, 201, 61));
        statusbar = new QStatusBar(DeveloperMenu);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 21));
        outputTextArea = new QTextEdit(DeveloperMenu);
        outputTextArea->setObjectName("outputTextArea");
        outputTextArea->setGeometry(QRect(40, 390, 631, 201));
        outputTextArea->setReadOnly(true);

        retranslateUi(DeveloperMenu);

        QMetaObject::connectSlotsByName(DeveloperMenu);
    } // setupUi

    void retranslateUi(QWidget *DeveloperMenu)
    {
        DeveloperMenu->setWindowTitle(QCoreApplication::translate("DeveloperMenu", "Developer Options", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
"      font-size: 24px;\n"
"      font-weight: bold;\n"
"      color: #2C3E50;\n"
"     ", nullptr));
        titleLabel->setText(QCoreApplication::translate("DeveloperMenu", "Developer Options", nullptr));
        gameNameInput->setPlaceholderText(QCoreApplication::translate("DeveloperMenu", "Enter game name", nullptr));
        versionComboBox->setItemText(0, QCoreApplication::translate("DeveloperMenu", "Pre_Alpha", nullptr));
        versionComboBox->setItemText(1, QCoreApplication::translate("DeveloperMenu", "Alpha", nullptr));
        versionComboBox->setItemText(2, QCoreApplication::translate("DeveloperMenu", "Beta", nullptr));
        versionComboBox->setItemText(3, QCoreApplication::translate("DeveloperMenu", "Release Candidate", nullptr));
        versionComboBox->setItemText(4, QCoreApplication::translate("DeveloperMenu", "General Availability", nullptr));

        createButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        createButton->setText(QCoreApplication::translate("DeveloperMenu", "Create Game", nullptr));
        findButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        findButton->setText(QCoreApplication::translate("DeveloperMenu", "Find Game", nullptr));
        readGamesButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        readGamesButton->setText(QCoreApplication::translate("DeveloperMenu", "Read Games", nullptr));
        backButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        backButton->setText(QCoreApplication::translate("DeveloperMenu", "Back", nullptr));
        deleteButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        deleteButton->setText(QCoreApplication::translate("DeveloperMenu", "Delete Game", nullptr));
        updateButton->setStyleSheet(QCoreApplication::translate("DeveloperMenu", "\n"
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
        updateButton->setText(QCoreApplication::translate("DeveloperMenu", "Update Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeveloperMenu: public Ui_DeveloperMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVELOPERMENU_H
