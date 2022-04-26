#include "uilogin.h"
#include "ui_uilogin.h"
#include <QDebug>
#include <QMessageBox>

UiLogin::UiLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UiLogin)
{
    ui->setupUi(this);


    QPixmap pixmap("../ui/login.png");//打开显示的图片
    pixmap.scaled(ui->labelback->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->labelback->setScaledContents(true);
    ui->labelback->setPixmap(pixmap);//标签显示图片

    ui->n1->setStyleSheet("border-image:url(../ui/1.png)");
    ui->n2->setStyleSheet("border-image:url(../ui/2.png)");
    ui->n3->setStyleSheet("border-image:url(../ui/3.png)");
    ui->n4->setStyleSheet("border-image:url(../ui/4.png)");
    ui->n5->setStyleSheet("border-image:url(../ui/5.png)");
    ui->n6->setStyleSheet("border-image:url(../ui/6.png)");
    ui->n7->setStyleSheet("border-image:url(../ui/7.png)");
    ui->n8->setStyleSheet("border-image:url(../ui/8.png)");
    ui->n9->setStyleSheet("border-image:url(../ui/9.png)");
    ui->n0->setStyleSheet("border-image:url(../ui/0.png)");
    ui->login->setStyleSheet("border-image:url(../ui/ok.png)");
    ui->ncl->setStyleSheet("border-image:url(../ui/cl.png)");
    ui->exit1->setStyleSheet("border-image:url(../ui/clo.png)");

    pwd = 0;

}

void UiLogin::get_pwd_sudo(int pwd)
{
    this->pwd_sudo = pwd;
}

void UiLogin::on_login_clicked()
{
    if(pwd == pwd_sudo)
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,"提示","管理员密码错误",QMessageBox::Ok);
    }
    on_ncl_clicked();
}

UiLogin::~UiLogin()
{
    delete ui;
}

void UiLogin::on_exit1_clicked()
{
    close();
}


//数字键盘
void UiLogin::on_ncl_clicked()
{
    pwd=0;
    ui->lcdNumber->display("0");//清空lcd数字显示屏幕
}

void UiLogin::on_n0_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+0;
         ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n1_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+1;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n2_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+2;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n3_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+3;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n4_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+4;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n5_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+5;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n6_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+6;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n7_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+7;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n8_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+8;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void UiLogin::on_n9_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+9;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}




