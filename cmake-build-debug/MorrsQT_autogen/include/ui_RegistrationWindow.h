/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWindow
{
public:
    QLineEdit *nameLineEdit;
    QLineEdit *ageLineEdit;
    QLineEdit *passwordLineEdit;
    QComboBox *genderComboBox;
    QComboBox *roleComboBox;
    QPushButton *saveButton;
    QPushButton *backButton;

    void setupUi(QWidget *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName("RegistrationWindow");
        RegistrationWindow->resize(730, 527);
        nameLineEdit = new QLineEdit(RegistrationWindow);
        nameLineEdit->setObjectName("nameLineEdit");
        nameLineEdit->setGeometry(QRect(180, 40, 331, 42));
        nameLineEdit->setStyleSheet(QString::fromUtf8("\n"
"                    QLineEdit {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        ageLineEdit = new QLineEdit(RegistrationWindow);
        ageLineEdit->setObjectName("ageLineEdit");
        ageLineEdit->setGeometry(QRect(180, 90, 331, 42));
        ageLineEdit->setStyleSheet(QString::fromUtf8("\n"
"                    QLineEdit {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        passwordLineEdit = new QLineEdit(RegistrationWindow);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(180, 140, 331, 42));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("\n"
"                    QLineEdit {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        genderComboBox = new QComboBox(RegistrationWindow);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");
        genderComboBox->setGeometry(QRect(180, 190, 331, 42));
        genderComboBox->setStyleSheet(QString::fromUtf8("\n"
"                    QComboBox {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        roleComboBox = new QComboBox(RegistrationWindow);
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->setObjectName("roleComboBox");
        roleComboBox->setGeometry(QRect(180, 240, 331, 42));
        roleComboBox->setStyleSheet(QString::fromUtf8("\n"
"                    QComboBox {\n"
"                    border-radius: 10px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                "));
        saveButton = new QPushButton(RegistrationWindow);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(290, 300, 111, 51));
        saveButton->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"                    background-color: #8E44AD;\n"
"                    color: white;\n"
"                    border-radius: 20px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                    QPushButton:hover {\n"
"                    background-color: #E67E22;\n"
"                    }"));
        backButton = new QPushButton(RegistrationWindow);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(580, 460, 131, 51));

        retranslateUi(RegistrationWindow);

        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QWidget *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QCoreApplication::translate("RegistrationWindow", "RegistrationWindow", nullptr));
        nameLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Enter your name", nullptr));
        ageLineEdit->setInputMask(QString());
        ageLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Enter your age", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Enter your password", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("RegistrationWindow", "Male", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("RegistrationWindow", "Female", nullptr));

        roleComboBox->setItemText(0, QCoreApplication::translate("RegistrationWindow", "Developer", nullptr));
        roleComboBox->setItemText(1, QCoreApplication::translate("RegistrationWindow", "Gamer", nullptr));
        roleComboBox->setItemText(2, QCoreApplication::translate("RegistrationWindow", "Administrator", nullptr));

        saveButton->setText(QCoreApplication::translate("RegistrationWindow", "Save", nullptr));
        backButton->setStyleSheet(QCoreApplication::translate("RegistrationWindow", "\n"
"                    QPushButton {\n"
"                    background-color: #F39C12;\n"
"                    color: white;\n"
"                    border-radius: 20px;\n"
"                    padding: 10px;\n"
"                    }\n"
"                    QPushButton:hover {\n"
"                    background-color: #E67E22;\n"
"                    }\n"
"                ", nullptr));
        backButton->setText(QCoreApplication::translate("RegistrationWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H
