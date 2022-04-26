/********************************************************************************
** Form generated from reading UI file 'open_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPEN_INTERFACE_H
#define UI_OPEN_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_open_interface
{
public:
    QLabel *face;
    QLCDNumber *lcdNumber;
    QPushButton *n0;
    QPushButton *n6;
    QPushButton *n8;
    QPushButton *n4;
    QPushButton *n1;
    QPushButton *nok;
    QPushButton *n3;
    QPushButton *n9;
    QPushButton *n2;
    QPushButton *n7;
    QPushButton *n5;
    QPushButton *ncl;
    QLabel *word;
    QPushButton *clo;
    QLabel *back;

    void setupUi(QWidget *open_interface)
    {
        if (open_interface->objectName().isEmpty())
            open_interface->setObjectName(QStringLiteral("open_interface"));
        open_interface->resize(800, 480);
        face = new QLabel(open_interface);
        face->setObjectName(QStringLiteral("face"));
        face->setGeometry(QRect(0, 0, 450, 480));
        face->setStyleSheet(QStringLiteral(""));
        lcdNumber = new QLCDNumber(open_interface);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(470, 90, 311, 111));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(18, 150, 219);"));
        lcdNumber->setDigitCount(6);
        lcdNumber->setMode(QLCDNumber::Oct);
        n0 = new QPushButton(open_interface);
        n0->setObjectName(QStringLiteral("n0"));
        n0->setGeometry(QRect(710, 220, 80, 80));
        n0->setMinimumSize(QSize(20, 20));
        n6 = new QPushButton(open_interface);
        n6->setObjectName(QStringLiteral("n6"));
        n6->setGeometry(QRect(630, 300, 80, 80));
        n6->setMinimumSize(QSize(20, 20));
        n8 = new QPushButton(open_interface);
        n8->setObjectName(QStringLiteral("n8"));
        n8->setGeometry(QRect(550, 380, 80, 80));
        n8->setMinimumSize(QSize(20, 20));
        n4 = new QPushButton(open_interface);
        n4->setObjectName(QStringLiteral("n4"));
        n4->setGeometry(QRect(470, 300, 80, 80));
        n4->setMinimumSize(QSize(20, 20));
        n1 = new QPushButton(open_interface);
        n1->setObjectName(QStringLiteral("n1"));
        n1->setGeometry(QRect(470, 220, 80, 80));
        n1->setMinimumSize(QSize(20, 20));
        nok = new QPushButton(open_interface);
        nok->setObjectName(QStringLiteral("nok"));
        nok->setGeometry(QRect(710, 380, 80, 80));
        nok->setMinimumSize(QSize(20, 20));
        n3 = new QPushButton(open_interface);
        n3->setObjectName(QStringLiteral("n3"));
        n3->setGeometry(QRect(630, 220, 80, 80));
        n3->setMinimumSize(QSize(20, 20));
        n9 = new QPushButton(open_interface);
        n9->setObjectName(QStringLiteral("n9"));
        n9->setGeometry(QRect(630, 380, 80, 80));
        n9->setMinimumSize(QSize(20, 20));
        n2 = new QPushButton(open_interface);
        n2->setObjectName(QStringLiteral("n2"));
        n2->setGeometry(QRect(550, 220, 80, 80));
        n2->setMinimumSize(QSize(20, 20));
        n7 = new QPushButton(open_interface);
        n7->setObjectName(QStringLiteral("n7"));
        n7->setGeometry(QRect(470, 380, 80, 80));
        n7->setMinimumSize(QSize(20, 20));
        n5 = new QPushButton(open_interface);
        n5->setObjectName(QStringLiteral("n5"));
        n5->setGeometry(QRect(550, 300, 80, 80));
        n5->setMinimumSize(QSize(20, 20));
        ncl = new QPushButton(open_interface);
        ncl->setObjectName(QStringLiteral("ncl"));
        ncl->setGeometry(QRect(710, 300, 80, 80));
        ncl->setMinimumSize(QSize(20, 20));
        word = new QLabel(open_interface);
        word->setObjectName(QStringLiteral("word"));
        word->setGeometry(QRect(490, 20, 241, 61));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(16);
        word->setFont(font);
        clo = new QPushButton(open_interface);
        clo->setObjectName(QStringLiteral("clo"));
        clo->setGeometry(QRect(699, 0, 101, 71));
        clo->setMinimumSize(QSize(20, 20));
        back = new QLabel(open_interface);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(0, 0, 800, 480));
        back->raise();
        face->raise();
        lcdNumber->raise();
        n0->raise();
        n6->raise();
        n8->raise();
        n4->raise();
        n1->raise();
        nok->raise();
        n3->raise();
        n9->raise();
        n2->raise();
        n7->raise();
        n5->raise();
        ncl->raise();
        word->raise();
        clo->raise();

        retranslateUi(open_interface);

        QMetaObject::connectSlotsByName(open_interface);
    } // setupUi

    void retranslateUi(QWidget *open_interface)
    {
        open_interface->setWindowTitle(QApplication::translate("open_interface", "Form", 0));
        face->setText(QString());
        n0->setText(QString());
        n6->setText(QString());
        n8->setText(QString());
        n4->setText(QString());
        n1->setText(QString());
        nok->setText(QString());
        n3->setText(QString());
        n9->setText(QString());
        n2->setText(QString());
        n7->setText(QString());
        n5->setText(QString());
        ncl->setText(QString());
        word->setText(QString());
        clo->setText(QString());
        back->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class open_interface: public Ui_open_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEN_INTERFACE_H
