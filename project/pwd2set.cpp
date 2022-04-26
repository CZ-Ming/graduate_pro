#include "pwd2set.h"
#include "ui_pwd2set.h"

pwd2set::pwd2set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pwd2set)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存

    QPixmap pixmap("../ui/pwd2.png");//打开显示的图片
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
    ui->nok->setStyleSheet("border-image:url(../ui/ok.png)");
    ui->ncl->setStyleSheet("border-image:url(../ui/cl.png)");
    ui->check->setStyleSheet("border-image:url(../ui/check.png)");
    ui->state->setStyleSheet("border-image:url(../ui/state.png)");
    ui->exit1->setStyleSheet("border-image:url(../ui/clo.png)");

    flag  =0;
    ui->textmsg->append("请输入原密码：");
}
void pwd2set::get_pwd2(int pwd2)
{
    this->pwd2 = pwd2;
}


//输入密码按确认键
void pwd2set::on_nok_clicked()
{
    switch(flag)
    {
        case 0:
        {
            if(pwd2 == pwd)
            {
                flag = 1;
                ui->textmsg->append("验证成功");
                ui->textmsg->append("请输入新密码");
            }
            else
            {
                ui->textmsg->append("验证失败");
                ui->textmsg->append("请重新输入原始密码");
            }
        }break;

        case 1:
        {
            flag =2;
            ui->textmsg->append("密码输入成功");
            ui->textmsg->append("请再次输入新密码");
            pwd2 = pwd;

        }break;

        case 2:
        {
            if(pwd2 == pwd)
            {
                ui->textmsg->append("密码输入成功");
                ui->textmsg->append("新密码已保存");
            }
            else
            {
                ui->textmsg->append("两次密码输入不一致");
                ui->textmsg->append("请重新输入");
                flag =1;
            }
        }break;
    }
    on_ncl_clicked();
}

//点击密码验证按钮
void pwd2set::on_check_clicked()
{
    if(pwd2 == pwd)
        ui->textmsg->append("密码正确");
    else
        ui->textmsg->append("密码错误");
    on_ncl_clicked();
}


//点击退出按钮
void pwd2set::on_exit1_clicked()
{
    emit sendpwd2(pwd2);
    emit sendsignal();
    this->close();
}

pwd2set::~pwd2set()
{
    delete ui;
}

void pwd2set::on_state_clicked()
{

}



//数字键盘
void pwd2set::on_ncl_clicked()
{
    pwd=0;
    ui->lcdNumber->display("0");//清空lcd数字显示屏幕
}

void pwd2set::on_n0_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+0;
         ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n1_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+1;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n2_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+2;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n3_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+3;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}



void pwd2set::on_n4_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+4;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n5_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+5;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n6_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+6;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}



void pwd2set::on_n7_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+7;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n8_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+8;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void pwd2set::on_n9_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+9;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}




