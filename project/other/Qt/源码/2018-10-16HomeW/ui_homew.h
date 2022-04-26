/********************************************************************************
** Form generated from reading UI file 'homew.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEW_H
#define UI_HOMEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeW
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *addBt;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *sizeLabel;
    QSpacerItem *verticalSpacer;
    QLCDNumber *lcdNumber;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSlider *redSd;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *greenSd;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSlider *blueSd;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *HomeW)
    {
        if (HomeW->objectName().isEmpty())
            HomeW->setObjectName(QStringLiteral("HomeW"));
        HomeW->resize(692, 422);
        HomeW->setStyleSheet(QLatin1String("QPushButton{\n"
"	color:#ff0000;\n"
"	border-radius:15px;\n"
"	border-color:#0000ff;\n"
"	border:2px solid #3f3f55;\n"
"\n"
"}\n"
"\n"
"QLabel{\n"
"	color:#ff0000;\n"
"	border-radius:10px;\n"
"	border-color:#0000ff;\n"
"	border:2px solid #3f3f55;\n"
"}\n"
"\n"
"QListWidget{\n"
"	color:#ff0000;\n"
"	border-radius:30px;\n"
"	border-color:#0000ff;\n"
"	border:2px solid #3f3f55;\n"
"	background-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QPushButton#addBt{\n"
"	color:#00ff00;\n"
"}"));
        centralWidget = new QWidget(HomeW);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addBt = new QPushButton(centralWidget);
        addBt->setObjectName(QStringLiteral("addBt"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addBt->sizePolicy().hasHeightForWidth());
        addBt->setSizePolicy(sizePolicy);
        addBt->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(addBt);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(listWidget);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setMinimumSize(QSize(120, 40));
        nameLabel->setStyleSheet(QLatin1String("color:#00ff00;\n"
"border-radius:5px;\n"
"border-color:#0000ff;\n"
"border:2px solid #3f3f55;"));

        horizontalLayout->addWidget(nameLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sizeLabel = new QLabel(centralWidget);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));
        sizeLabel->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(sizeLabel);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 80));
        lcdNumber->setDigitCount(8);

        verticalLayout_3->addWidget(lcdNumber);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        redSd = new QSlider(centralWidget);
        redSd->setObjectName(QStringLiteral("redSd"));
        redSd->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(redSd);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        greenSd = new QSlider(centralWidget);
        greenSd->setObjectName(QStringLiteral("greenSd"));
        greenSd->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(greenSd);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        blueSd = new QSlider(centralWidget);
        blueSd->setObjectName(QStringLiteral("blueSd"));
        blueSd->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(blueSd);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_5->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        HomeW->setCentralWidget(centralWidget);

        retranslateUi(HomeW);

        QMetaObject::connectSlotsByName(HomeW);
    } // setupUi

    void retranslateUi(QMainWindow *HomeW)
    {
        HomeW->setWindowTitle(QApplication::translate("HomeW", "HomeW", 0));
        addBt->setText(QApplication::translate("HomeW", "\346\267\273\345\212\240\346\226\207\344\273\266", 0));
        nameLabel->setText(QApplication::translate("HomeW", "name", 0));
        sizeLabel->setText(QApplication::translate("HomeW", "size", 0));
        label_3->setText(QApplication::translate("HomeW", "R", 0));
        label_4->setText(QApplication::translate("HomeW", "G", 0));
        label_5->setText(QApplication::translate("HomeW", "B", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeW: public Ui_HomeW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEW_H
