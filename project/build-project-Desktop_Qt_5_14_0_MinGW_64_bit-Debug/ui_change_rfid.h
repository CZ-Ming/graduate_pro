/********************************************************************************
** Form generated from reading UI file 'change_rfid.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_RFID_H
#define UI_CHANGE_RFID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_change_rfid
{
public:
    QTextEdit *rfidedit;
    QLabel *label_2;
    QLabel *label;
    QPushButton *n7;
    QPushButton *n8;
    QPushButton *n2;
    QPushButton *ncl;
    QPushButton *n4;
    QPushButton *n5;
    QPushButton *n9;
    QPushButton *n3;
    QPushButton *n0;
    QPushButton *n1;
    QPushButton *n6;
    QPushButton *nok;
    QLCDNumber *lcdNumber;
    QPushButton *addexit;
    QLabel *back;
    QPushButton *card;
    QPushButton *password;

    void setupUi(QWidget *change_rfid)
    {
        if (change_rfid->objectName().isEmpty())
            change_rfid->setObjectName(QString::fromUtf8("change_rfid"));
        change_rfid->resize(800, 480);
        rfidedit = new QTextEdit(change_rfid);
        rfidedit->setObjectName(QString::fromUtf8("rfidedit"));
        rfidedit->setGeometry(QRect(0, 80, 451, 331));
        rfidedit->setMinimumSize(QSize(20, 20));
        rfidedit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));
        label_2 = new QLabel(change_rfid);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(470, 30, 231, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(14);
        label_2->setFont(font);
        label = new QLabel(change_rfid);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 20, 171, 31));
        label->setFont(font);
        n7 = new QPushButton(change_rfid);
        n7->setObjectName(QString::fromUtf8("n7"));
        n7->setGeometry(QRect(470, 330, 80, 80));
        n7->setMinimumSize(QSize(20, 20));
        n8 = new QPushButton(change_rfid);
        n8->setObjectName(QString::fromUtf8("n8"));
        n8->setGeometry(QRect(550, 330, 80, 80));
        n8->setMinimumSize(QSize(20, 20));
        n2 = new QPushButton(change_rfid);
        n2->setObjectName(QString::fromUtf8("n2"));
        n2->setGeometry(QRect(550, 170, 80, 80));
        n2->setMinimumSize(QSize(20, 20));
        ncl = new QPushButton(change_rfid);
        ncl->setObjectName(QString::fromUtf8("ncl"));
        ncl->setGeometry(QRect(710, 250, 80, 80));
        ncl->setMinimumSize(QSize(20, 20));
        n4 = new QPushButton(change_rfid);
        n4->setObjectName(QString::fromUtf8("n4"));
        n4->setGeometry(QRect(470, 250, 80, 80));
        n4->setMinimumSize(QSize(20, 20));
        n5 = new QPushButton(change_rfid);
        n5->setObjectName(QString::fromUtf8("n5"));
        n5->setGeometry(QRect(550, 250, 80, 80));
        n5->setMinimumSize(QSize(20, 20));
        n9 = new QPushButton(change_rfid);
        n9->setObjectName(QString::fromUtf8("n9"));
        n9->setGeometry(QRect(630, 330, 80, 80));
        n9->setMinimumSize(QSize(20, 20));
        n3 = new QPushButton(change_rfid);
        n3->setObjectName(QString::fromUtf8("n3"));
        n3->setGeometry(QRect(630, 170, 80, 80));
        n3->setMinimumSize(QSize(20, 20));
        n0 = new QPushButton(change_rfid);
        n0->setObjectName(QString::fromUtf8("n0"));
        n0->setGeometry(QRect(710, 170, 80, 80));
        n0->setMinimumSize(QSize(20, 20));
        n1 = new QPushButton(change_rfid);
        n1->setObjectName(QString::fromUtf8("n1"));
        n1->setGeometry(QRect(470, 170, 80, 80));
        n1->setMinimumSize(QSize(20, 20));
        n6 = new QPushButton(change_rfid);
        n6->setObjectName(QString::fromUtf8("n6"));
        n6->setGeometry(QRect(630, 250, 80, 80));
        n6->setMinimumSize(QSize(20, 20));
        nok = new QPushButton(change_rfid);
        nok->setObjectName(QString::fromUtf8("nok"));
        nok->setGeometry(QRect(710, 330, 80, 80));
        nok->setMinimumSize(QSize(20, 20));
        lcdNumber = new QLCDNumber(change_rfid);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(470, 80, 321, 81));
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(18, 150, 219);"));
        lcdNumber->setDigitCount(6);
        lcdNumber->setMode(QLCDNumber::Oct);
        addexit = new QPushButton(change_rfid);
        addexit->setObjectName(QString::fromUtf8("addexit"));
        addexit->setGeometry(QRect(700, 10, 91, 61));
        addexit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 127);"));
        back = new QLabel(change_rfid);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(0, 0, 800, 480));
        card = new QPushButton(change_rfid);
        card->setObjectName(QString::fromUtf8("card"));
        card->setGeometry(QRect(20, 420, 131, 61));
        card->setMinimumSize(QSize(20, 20));
        password = new QPushButton(change_rfid);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(240, 420, 131, 61));
        password->setMinimumSize(QSize(20, 20));
        back->raise();
        rfidedit->raise();
        label_2->raise();
        label->raise();
        n7->raise();
        n8->raise();
        n2->raise();
        ncl->raise();
        n4->raise();
        n5->raise();
        n9->raise();
        n3->raise();
        n0->raise();
        n1->raise();
        n6->raise();
        nok->raise();
        lcdNumber->raise();
        addexit->raise();
        card->raise();
        password->raise();

        retranslateUi(change_rfid);

        QMetaObject::connectSlotsByName(change_rfid);
    } // setupUi

    void retranslateUi(QWidget *change_rfid)
    {
        change_rfid->setWindowTitle(QCoreApplication::translate("change_rfid", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("change_rfid", "\350\257\267\350\276\223\345\205\245\346\226\2606\344\275\215\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("change_rfid", "RFID\347\256\241\347\220\206\347\225\214\351\235\242", nullptr));
        n7->setText(QString());
        n8->setText(QString());
        n2->setText(QString());
        ncl->setText(QString());
        n4->setText(QString());
        n5->setText(QString());
        n9->setText(QString());
        n3->setText(QString());
        n0->setText(QString());
        n1->setText(QString());
        n6->setText(QString());
        nok->setText(QString());
        addexit->setText(QString());
        back->setText(QString());
        card->setText(QString());
        password->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class change_rfid: public Ui_change_rfid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_RFID_H
