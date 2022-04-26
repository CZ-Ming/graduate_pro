/********************************************************************************
** Form generated from reading UI file 'uilogin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UILOGIN_H
#define UI_UILOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UiLogin
{
public:
    QPushButton *n7;
    QPushButton *n2;
    QPushButton *n6;
    QPushButton *n4;
    QPushButton *n3;
    QLCDNumber *lcdNumber;
    QPushButton *n5;
    QPushButton *n9;
    QPushButton *n1;
    QPushButton *n0;
    QPushButton *n8;
    QPushButton *login;
    QPushButton *exit1;
    QPushButton *ncl;
    QLabel *labelback;

    void setupUi(QDialog *UiLogin)
    {
        if (UiLogin->objectName().isEmpty())
            UiLogin->setObjectName(QStringLiteral("UiLogin"));
        UiLogin->resize(800, 480);
        n7 = new QPushButton(UiLogin);
        n7->setObjectName(QStringLiteral("n7"));
        n7->setGeometry(QRect(210, 370, 80, 80));
        n7->setMinimumSize(QSize(20, 20));
        n2 = new QPushButton(UiLogin);
        n2->setObjectName(QStringLiteral("n2"));
        n2->setGeometry(QRect(290, 210, 80, 80));
        n2->setMinimumSize(QSize(20, 20));
        n6 = new QPushButton(UiLogin);
        n6->setObjectName(QStringLiteral("n6"));
        n6->setGeometry(QRect(370, 290, 80, 80));
        n6->setMinimumSize(QSize(20, 20));
        n4 = new QPushButton(UiLogin);
        n4->setObjectName(QStringLiteral("n4"));
        n4->setGeometry(QRect(210, 290, 80, 80));
        n4->setMinimumSize(QSize(20, 20));
        n3 = new QPushButton(UiLogin);
        n3->setObjectName(QStringLiteral("n3"));
        n3->setGeometry(QRect(370, 210, 80, 80));
        n3->setMinimumSize(QSize(20, 20));
        lcdNumber = new QLCDNumber(UiLogin);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(210, 130, 321, 71));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(18, 150, 219);"));
        lcdNumber->setDigitCount(6);
        lcdNumber->setMode(QLCDNumber::Oct);
        n5 = new QPushButton(UiLogin);
        n5->setObjectName(QStringLiteral("n5"));
        n5->setGeometry(QRect(290, 290, 80, 80));
        n5->setMinimumSize(QSize(20, 20));
        n9 = new QPushButton(UiLogin);
        n9->setObjectName(QStringLiteral("n9"));
        n9->setGeometry(QRect(370, 370, 80, 80));
        n9->setMinimumSize(QSize(20, 20));
        n1 = new QPushButton(UiLogin);
        n1->setObjectName(QStringLiteral("n1"));
        n1->setGeometry(QRect(210, 210, 80, 80));
        n1->setMinimumSize(QSize(20, 20));
        n0 = new QPushButton(UiLogin);
        n0->setObjectName(QStringLiteral("n0"));
        n0->setGeometry(QRect(450, 210, 80, 80));
        n0->setMinimumSize(QSize(20, 20));
        n8 = new QPushButton(UiLogin);
        n8->setObjectName(QStringLiteral("n8"));
        n8->setGeometry(QRect(290, 370, 80, 80));
        n8->setMinimumSize(QSize(20, 20));
        login = new QPushButton(UiLogin);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(450, 370, 80, 80));
        login->setMinimumSize(QSize(20, 20));
        exit1 = new QPushButton(UiLogin);
        exit1->setObjectName(QStringLiteral("exit1"));
        exit1->setGeometry(QRect(679, 10, 111, 71));
        exit1->setMinimumSize(QSize(20, 20));
        ncl = new QPushButton(UiLogin);
        ncl->setObjectName(QStringLiteral("ncl"));
        ncl->setGeometry(QRect(450, 290, 80, 80));
        ncl->setMinimumSize(QSize(20, 20));
        labelback = new QLabel(UiLogin);
        labelback->setObjectName(QStringLiteral("labelback"));
        labelback->setGeometry(QRect(0, 0, 800, 480));
        labelback->raise();
        n7->raise();
        n2->raise();
        n6->raise();
        n4->raise();
        n3->raise();
        lcdNumber->raise();
        n5->raise();
        n9->raise();
        n1->raise();
        n0->raise();
        n8->raise();
        login->raise();
        exit1->raise();
        ncl->raise();

        retranslateUi(UiLogin);

        QMetaObject::connectSlotsByName(UiLogin);
    } // setupUi

    void retranslateUi(QDialog *UiLogin)
    {
        UiLogin->setWindowTitle(QApplication::translate("UiLogin", "\350\264\252\347\216\251\350\223\235\346\234\210", 0));
        n7->setText(QString());
        n2->setText(QString());
        n6->setText(QString());
        n4->setText(QString());
        n3->setText(QString());
        n5->setText(QString());
        n9->setText(QString());
        n1->setText(QString());
        n0->setText(QString());
        n8->setText(QString());
        login->setText(QString());
        exit1->setText(QString());
        ncl->setText(QString());
        labelback->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UiLogin: public Ui_UiLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UILOGIN_H
