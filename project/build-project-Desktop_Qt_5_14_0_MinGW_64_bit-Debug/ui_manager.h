/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_manager
{
public:
    QPushButton *finger;
    QPushButton *pass;
    QPushButton *rfid;
    QLabel *label;
    QPushButton *exit1;

    void setupUi(QWidget *manager)
    {
        if (manager->objectName().isEmpty())
            manager->setObjectName(QString::fromUtf8("manager"));
        manager->resize(800, 480);
        finger = new QPushButton(manager);
        finger->setObjectName(QString::fromUtf8("finger"));
        finger->setGeometry(QRect(55, 184, 165, 161));
        pass = new QPushButton(manager);
        pass->setObjectName(QString::fromUtf8("pass"));
        pass->setGeometry(QRect(307, 186, 166, 161));
        rfid = new QPushButton(manager);
        rfid->setObjectName(QString::fromUtf8("rfid"));
        rfid->setGeometry(QRect(565, 184, 165, 160));
        label = new QLabel(manager);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        exit1 = new QPushButton(manager);
        exit1->setObjectName(QString::fromUtf8("exit1"));
        exit1->setGeometry(QRect(690, 10, 91, 81));
        label->raise();
        finger->raise();
        pass->raise();
        rfid->raise();
        exit1->raise();

        retranslateUi(manager);

        QMetaObject::connectSlotsByName(manager);
    } // setupUi

    void retranslateUi(QWidget *manager)
    {
        manager->setWindowTitle(QCoreApplication::translate("manager", "Form", nullptr));
        finger->setText(QString());
        pass->setText(QString());
        rfid->setText(QString());
        label->setText(QString());
        exit1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class manager: public Ui_manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
