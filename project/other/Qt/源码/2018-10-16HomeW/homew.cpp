#include "homew.h"
#include "ui_homew.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

HomeW::HomeW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeW)
{
    ui->setupUi(this);
    //全屏显示
    this->showFullScreen();
    //初始化定时器
    mtimer = new QTimer();
    connect(mtimer,SIGNAL(timeout()),this, SLOT(update_time()));
    //启动定时器
    mtimer ->start(1000);

    //设置进度条最大值
    ui->redSd->setMaximum(255);
    ui->greenSd->setMaximum(255);
    ui->blueSd->setMaximum(255);
}

HomeW::~HomeW()
{
    delete ui;
}

void HomeW::on_addBt_clicked()
{
    QString filepath =QFileDialog::getOpenFileName(this);
    ui->listWidget->addItem( filepath );
}

void HomeW::update_time()
{
    QString tim = QTime::currentTime().toString("hh:mm:ss");
    ui->lcdNumber->display(tim);
}

void HomeW::on_listWidget_doubleClicked(const QModelIndex &index)
{
    //从列表中获取当前向内容
    QString filepath = ui->listWidget->currentItem()->text();
    QFileInfo info(filepath);

    //设置显示
    ui->nameLabel->setText(info.fileName());
    ui->sizeLabel->setText(QString::number(info.size()));
}

void HomeW::on_redSd_sliderMoved(int position)
{
    int r = ui->redSd->value();
    int g = ui->greenSd->value();
    int b = ui->blueSd->value();

    ui->lcdNumber->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(r).arg(g).arg(b));

}

void HomeW::on_greenSd_sliderMoved(int position)
{
    int r = ui->redSd->value();
    int g = ui->greenSd->value();
    int b = ui->blueSd->value();

    ui->lcdNumber->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(r).arg(g).arg(b));
}

void HomeW::on_blueSd_sliderMoved(int position)
{
    int r = ui->redSd->value();
    int g = ui->greenSd->value();
    int b = ui->blueSd->value();

    ui->lcdNumber->setStyleSheet(QString("color:rgb(%1,%2,%3)").arg(r).arg(g).arg(b));
}
