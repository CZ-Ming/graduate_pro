/********************************************************************************
** Form generated from reading UI file 'pwd2set.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWD2SET_H
#define UI_PWD2SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pwd2set
{
public:
    QPushButton *n3;
    QPushButton *n6;
    QPushButton *n9;
    QPushButton *n1;
    QLCDNumber *lcdNumber;
    QPushButton *n5;
    QPushButton *n7;
    QPushButton *nok;
    QPushButton *n2;
    QPushButton *n0;
    QPushButton *n4;
    QPushButton *n8;
    QPushButton *ncl;
    QTextBrowser *textmsg;
    QLabel *labelback;
    QPushButton *check;
    QPushButton *state;
    QPushButton *exit1;

    void setupUi(QWidget *pwd2set)
    {
        if (pwd2set->objectName().isEmpty())
            pwd2set->setObjectName(QStringLiteral("pwd2set"));
        pwd2set->resize(800, 480);
        n3 = new QPushButton(pwd2set);
        n3->setObjectName(QStringLiteral("n3"));
        n3->setGeometry(QRect(540, 210, 80, 80));
        n3->setMinimumSize(QSize(20, 20));
        n6 = new QPushButton(pwd2set);
        n6->setObjectName(QStringLiteral("n6"));
        n6->setGeometry(QRect(540, 290, 80, 80));
        n6->setMinimumSize(QSize(20, 20));
        n9 = new QPushButton(pwd2set);
        n9->setObjectName(QStringLiteral("n9"));
        n9->setGeometry(QRect(540, 370, 80, 80));
        n9->setMinimumSize(QSize(20, 20));
        n1 = new QPushButton(pwd2set);
        n1->setObjectName(QStringLiteral("n1"));
        n1->setGeometry(QRect(380, 210, 80, 80));
        n1->setMinimumSize(QSize(20, 20));
        lcdNumber = new QLCDNumber(pwd2set);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(380, 80, 401, 111));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(18, 150, 219);"));
        lcdNumber->setDigitCount(6);
        lcdNumber->setMode(QLCDNumber::Oct);
        n5 = new QPushButton(pwd2set);
        n5->setObjectName(QStringLiteral("n5"));
        n5->setGeometry(QRect(460, 290, 80, 80));
        n5->setMinimumSize(QSize(20, 20));
        n7 = new QPushButton(pwd2set);
        n7->setObjectName(QStringLiteral("n7"));
        n7->setGeometry(QRect(380, 370, 80, 80));
        n7->setMinimumSize(QSize(20, 20));
        nok = new QPushButton(pwd2set);
        nok->setObjectName(QStringLiteral("nok"));
        nok->setGeometry(QRect(620, 370, 80, 80));
        nok->setMinimumSize(QSize(20, 20));
        n2 = new QPushButton(pwd2set);
        n2->setObjectName(QStringLiteral("n2"));
        n2->setGeometry(QRect(460, 210, 80, 80));
        n2->setMinimumSize(QSize(20, 20));
        n0 = new QPushButton(pwd2set);
        n0->setObjectName(QStringLiteral("n0"));
        n0->setGeometry(QRect(620, 210, 80, 80));
        n0->setMinimumSize(QSize(20, 20));
        n4 = new QPushButton(pwd2set);
        n4->setObjectName(QStringLiteral("n4"));
        n4->setGeometry(QRect(380, 290, 80, 80));
        n4->setMinimumSize(QSize(20, 20));
        n8 = new QPushButton(pwd2set);
        n8->setObjectName(QStringLiteral("n8"));
        n8->setGeometry(QRect(460, 370, 80, 80));
        n8->setMinimumSize(QSize(20, 20));
        ncl = new QPushButton(pwd2set);
        ncl->setObjectName(QStringLiteral("ncl"));
        ncl->setGeometry(QRect(620, 290, 80, 80));
        ncl->setMinimumSize(QSize(20, 20));
        textmsg = new QTextBrowser(pwd2set);
        textmsg->setObjectName(QStringLiteral("textmsg"));
        textmsg->setGeometry(QRect(0, 80, 371, 391));
        textmsg->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 255);"));
        labelback = new QLabel(pwd2set);
        labelback->setObjectName(QStringLiteral("labelback"));
        labelback->setGeometry(QRect(0, 0, 800, 480));
        check = new QPushButton(pwd2set);
        check->setObjectName(QStringLiteral("check"));
        check->setGeometry(QRect(700, 210, 80, 80));
        check->setMinimumSize(QSize(20, 20));
        state = new QPushButton(pwd2set);
        state->setObjectName(QStringLiteral("state"));
        state->setGeometry(QRect(700, 290, 80, 80));
        state->setMinimumSize(QSize(20, 20));
        exit1 = new QPushButton(pwd2set);
        exit1->setObjectName(QStringLiteral("exit1"));
        exit1->setGeometry(QRect(700, 370, 80, 80));
        exit1->setMinimumSize(QSize(20, 20));
        labelback->raise();
        n3->raise();
        n6->raise();
        n9->raise();
        n1->raise();
        lcdNumber->raise();
        n5->raise();
        n7->raise();
        nok->raise();
        n2->raise();
        n0->raise();
        n4->raise();
        n8->raise();
        ncl->raise();
        textmsg->raise();
        check->raise();
        state->raise();
        exit1->raise();

        retranslateUi(pwd2set);

        QMetaObject::connectSlotsByName(pwd2set);
    } // setupUi

    void retranslateUi(QWidget *pwd2set)
    {
        pwd2set->setWindowTitle(QApplication::translate("pwd2set", "Form", 0));
        n3->setText(QString());
        n6->setText(QString());
        n9->setText(QString());
        n1->setText(QString());
        n5->setText(QString());
        n7->setText(QString());
        nok->setText(QString());
        n2->setText(QString());
        n0->setText(QString());
        n4->setText(QString());
        n8->setText(QString());
        ncl->setText(QString());
        labelback->setText(QString());
        check->setText(QString());
        state->setText(QString());
        exit1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pwd2set: public Ui_pwd2set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWD2SET_H
