/********************************************************************************
** Form generated from reading UI file 'enterwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERWINDOW_H
#define UI_ENTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnterWindow
{
public:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *backButton;

    void setupUi(QWidget *EnterWindow)
    {
        if (EnterWindow->objectName().isEmpty())
            EnterWindow->setObjectName("EnterWindow");
        EnterWindow->resize(678, 463);
        usernameLineEdit = new QLineEdit(EnterWindow);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(200, 80, 281, 51));
        usernameLineEdit->setStyleSheet(QString::fromUtf8("\n"
"                    QLineEdit {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        passwordLineEdit = new QLineEdit(EnterWindow);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(200, 160, 281, 51));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("\n"
"                    QLineEdit {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        loginButton = new QPushButton(EnterWindow);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(260, 250, 151, 61));
        loginButton->setStyleSheet(QString::fromUtf8("      QPushButton {\n"
"          background-color: #8E44AD;\n"
"          color: white;\n"
"          border-radius: 20px;\n"
"          padding: 10px;\n"
"      }\n"
"      QPushButton:hover {\n"
"          background-color: #E67E22;\n"
"      }\n"
"     "));
        backButton = new QPushButton(EnterWindow);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(510, 380, 141, 61));

        retranslateUi(EnterWindow);

        QMetaObject::connectSlotsByName(EnterWindow);
    } // setupUi

    void retranslateUi(QWidget *EnterWindow)
    {
        EnterWindow->setWindowTitle(QCoreApplication::translate("EnterWindow", "\320\222\321\205\320\276\320\264", nullptr));
        usernameLineEdit->setText(QString());
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("EnterWindow", "Username", nullptr));
        passwordLineEdit->setText(QString());
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("EnterWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("EnterWindow", "Sign In", nullptr));
        backButton->setStyleSheet(QCoreApplication::translate("EnterWindow", "\n"
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
        backButton->setText(QCoreApplication::translate("EnterWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnterWindow: public Ui_EnterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERWINDOW_H
