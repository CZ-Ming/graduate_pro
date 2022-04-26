/********************************************************************************
** Form generated from reading UI file 'ledctl.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDCTL_H
#define UI_LEDCTL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LedCtl
{
public:
    QWidget *centralWidget;
    QPushButton *led1Bt;
    QPushButton *led2Bt;

    void setupUi(QMainWindow *LedCtl)
    {
        if (LedCtl->objectName().isEmpty())
            LedCtl->setObjectName(QStringLiteral("LedCtl"));
        LedCtl->resize(800, 480);
        centralWidget = new QWidget(LedCtl);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        led1Bt = new QPushButton(centralWidget);
        led1Bt->setObjectName(QStringLiteral("led1Bt"));
        led1Bt->setGeometry(QRect(20, 30, 151, 111));
        led2Bt = new QPushButton(centralWidget);
        led2Bt->setObjectName(QStringLiteral("led2Bt"));
        led2Bt->setGeometry(QRect(20, 250, 151, 111));
        LedCtl->setCentralWidget(centralWidget);

        retranslateUi(LedCtl);

        QMetaObject::connectSlotsByName(LedCtl);
    } // setupUi

    void retranslateUi(QMainWindow *LedCtl)
    {
        LedCtl->setWindowTitle(QApplication::translate("LedCtl", "LedCtl", 0));
        led1Bt->setText(QApplication::translate("LedCtl", "open", 0));
        led2Bt->setText(QApplication::translate("LedCtl", "open", 0));
    } // retranslateUi

};

namespace Ui {
    class LedCtl: public Ui_LedCtl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDCTL_H
