/********************************************************************************
** Form generated from reading UI file 'change_as608.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_AS608_H
#define UI_CHANGE_AS608_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_change_as608
{
public:
    QPushButton *addexit;
    QLabel *label;
    QPushButton *addfp;
    QTextEdit *msgtext;
    QPushButton *delfp;
    QPushButton *findfp;
    QPushButton *ncl;
    QPushButton *n2;
    QPushButton *nok;
    QPushButton *n5;
    QPushButton *n6;
    QPushButton *n1;
    QPushButton *n8;
    QPushButton *n4;
    QPushButton *n0;
    QPushButton *n3;
    QPushButton *n9;
    QPushButton *n7;
    QLCDNumber *lcdNumber;
    QLabel *back;
    QLabel *label_2;

    void setupUi(QWidget *change_as608)
    {
        if (change_as608->objectName().isEmpty())
            change_as608->setObjectName(QStringLiteral("change_as608"));
        change_as608->resize(800, 480);
        addexit = new QPushButton(change_as608);
        addexit->setObjectName(QStringLiteral("addexit"));
        addexit->setGeometry(QRect(690, 0, 91, 71));
        addexit->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 127);"));
        label = new QLabel(change_as608);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 20, 381, 41));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(18);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(""));
        addfp = new QPushButton(change_as608);
        addfp->setObjectName(QStringLiteral("addfp"));
        addfp->setGeometry(QRect(20, 420, 121, 51));
        msgtext = new QTextEdit(change_as608);
        msgtext->setObjectName(QStringLiteral("msgtext"));
        msgtext->setGeometry(QRect(0, 100, 441, 311));
        msgtext->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 255);"));
        delfp = new QPushButton(change_as608);
        delfp->setObjectName(QStringLiteral("delfp"));
        delfp->setGeometry(QRect(160, 420, 121, 51));
        findfp = new QPushButton(change_as608);
        findfp->setObjectName(QStringLiteral("findfp"));
        findfp->setGeometry(QRect(300, 420, 121, 51));
        ncl = new QPushButton(change_as608);
        ncl->setObjectName(QStringLiteral("ncl"));
        ncl->setGeometry(QRect(700, 280, 80, 80));
        ncl->setMinimumSize(QSize(20, 20));
        n2 = new QPushButton(change_as608);
        n2->setObjectName(QStringLiteral("n2"));
        n2->setGeometry(QRect(540, 200, 80, 80));
        n2->setMinimumSize(QSize(20, 20));
        nok = new QPushButton(change_as608);
        nok->setObjectName(QStringLiteral("nok"));
        nok->setGeometry(QRect(700, 360, 80, 80));
        nok->setMinimumSize(QSize(20, 20));
        n5 = new QPushButton(change_as608);
        n5->setObjectName(QStringLiteral("n5"));
        n5->setGeometry(QRect(540, 280, 80, 80));
        n5->setMinimumSize(QSize(20, 20));
        n6 = new QPushButton(change_as608);
        n6->setObjectName(QStringLiteral("n6"));
        n6->setGeometry(QRect(620, 280, 80, 80));
        n6->setMinimumSize(QSize(20, 20));
        n1 = new QPushButton(change_as608);
        n1->setObjectName(QStringLiteral("n1"));
        n1->setGeometry(QRect(460, 200, 80, 80));
        n1->setMinimumSize(QSize(20, 20));
        n8 = new QPushButton(change_as608);
        n8->setObjectName(QStringLiteral("n8"));
        n8->setGeometry(QRect(540, 360, 80, 80));
        n8->setMinimumSize(QSize(20, 20));
        n4 = new QPushButton(change_as608);
        n4->setObjectName(QStringLiteral("n4"));
        n4->setGeometry(QRect(460, 280, 80, 80));
        n4->setMinimumSize(QSize(20, 20));
        n0 = new QPushButton(change_as608);
        n0->setObjectName(QStringLiteral("n0"));
        n0->setGeometry(QRect(700, 200, 80, 80));
        n0->setMinimumSize(QSize(20, 20));
        n3 = new QPushButton(change_as608);
        n3->setObjectName(QStringLiteral("n3"));
        n3->setGeometry(QRect(620, 200, 80, 80));
        n3->setMinimumSize(QSize(20, 20));
        n9 = new QPushButton(change_as608);
        n9->setObjectName(QStringLiteral("n9"));
        n9->setGeometry(QRect(620, 360, 80, 80));
        n9->setMinimumSize(QSize(20, 20));
        n7 = new QPushButton(change_as608);
        n7->setObjectName(QStringLiteral("n7"));
        n7->setGeometry(QRect(460, 360, 80, 80));
        n7->setMinimumSize(QSize(20, 20));
        lcdNumber = new QLCDNumber(change_as608);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(460, 100, 321, 81));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(18, 150, 219);"));
        lcdNumber->setDigitCount(6);
        lcdNumber->setMode(QLCDNumber::Oct);
        back = new QLabel(change_as608);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(0, 0, 800, 480));
        label_2 = new QLabel(change_as608);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(550, 60, 131, 51));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("selection-color: rgb(255, 255, 255);"));
        back->raise();
        addexit->raise();
        label->raise();
        addfp->raise();
        msgtext->raise();
        delfp->raise();
        findfp->raise();
        ncl->raise();
        n2->raise();
        nok->raise();
        n5->raise();
        n6->raise();
        n1->raise();
        n8->raise();
        n4->raise();
        n0->raise();
        n3->raise();
        n9->raise();
        n7->raise();
        lcdNumber->raise();
        label_2->raise();

        retranslateUi(change_as608);

        QMetaObject::connectSlotsByName(change_as608);
    } // setupUi

    void retranslateUi(QWidget *change_as608)
    {
        change_as608->setWindowTitle(QApplication::translate("change_as608", "Form", 0));
        addexit->setText(QString());
        label->setText(QApplication::translate("change_as608", "\346\254\242\350\277\216\350\277\233\345\205\245\346\214\207\347\272\271\345\275\225\345\205\245\347\225\214\351\235\242", 0));
        addfp->setText(QApplication::translate("change_as608", "\346\214\207\347\272\271\345\275\225\345\210\266", 0));
        delfp->setText(QApplication::translate("change_as608", "\346\214\207\347\272\271\345\210\240\351\231\244", 0));
        findfp->setText(QApplication::translate("change_as608", "\346\214\207\347\272\271\346\237\245\350\257\242", 0));
        ncl->setText(QString());
        n2->setText(QString());
        nok->setText(QString());
        n5->setText(QString());
        n6->setText(QString());
        n1->setText(QString());
        n8->setText(QString());
        n4->setText(QString());
        n0->setText(QString());
        n3->setText(QString());
        n9->setText(QString());
        n7->setText(QString());
        back->setText(QApplication::translate("change_as608", "TextLabel", 0));
        label_2->setText(QApplication::translate("change_as608", "\350\276\223\345\205\245\346\214\207\347\272\271ID\345\217\267", 0));
    } // retranslateUi

};

namespace Ui {
    class change_as608: public Ui_change_as608 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_AS608_H
