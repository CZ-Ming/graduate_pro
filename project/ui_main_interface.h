/********************************************************************************
** Form generated from reading UI file 'main_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_INTERFACE_H
#define UI_MAIN_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_interface
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *lock;
    QPushButton *manage;

    void setupUi(QMainWindow *main_interface)
    {
        if (main_interface->objectName().isEmpty())
            main_interface->setObjectName(QStringLiteral("main_interface"));
        main_interface->resize(800, 480);
        centralwidget = new QWidget(main_interface);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        lock = new QPushButton(centralwidget);
        lock->setObjectName(QStringLiteral("lock"));
        lock->setGeometry(QRect(100, 160, 179, 213));
        manage = new QPushButton(centralwidget);
        manage->setObjectName(QStringLiteral("manage"));
        manage->setGeometry(QRect(424, 164, 192, 206));
        main_interface->setCentralWidget(centralwidget);

        retranslateUi(main_interface);

        QMetaObject::connectSlotsByName(main_interface);
    } // setupUi

    void retranslateUi(QMainWindow *main_interface)
    {
        main_interface->setWindowTitle(QApplication::translate("main_interface", "main_interface", 0));
        label->setText(QString());
        lock->setText(QString());
        manage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class main_interface: public Ui_main_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_INTERFACE_H
