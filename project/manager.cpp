#include "manager.h"
#include "ui_manager.h"

using namespace std;

manager::manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存

    QPixmap pixmap("../ui/manager.png");//打开显示的图片
    pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->label->setScaledContents(true);
    ui->label->setPixmap(pixmap);//标签显示图片

    ui->finger->setStyleSheet("border-image:url(../ui/finger.png)");
    ui->pass->setStyleSheet("border-image:url(../ui/pass.png)");
    ui->rfid->setStyleSheet("border-image:url(../ui/rfid.png)");
    ui->exit1->setStyleSheet("border-image:url(../ui/clo.png)");

}


//获取主界面的密码
void manager::getpwd2(int pwd2)
{
    this->pwd2 = pwd2;
}
//设置新密码
void manager::set_pwd2(int pwd2)
{
    this->pwd2 = pwd2;
    emit sendpwd2(pwd2);
}
//获取主界面的密码
void manager::getpwd1(int pwd1)
{
    this->pwd1 = pwd1;
}
//设置新密码
void manager::set_pwd1(int pwd1)
{
    this->pwd1 = pwd1;
    emit sendpwd1(pwd1);
}


//修改数字密码
void manager::on_pass_clicked()
{

    this->hide();//主界面隐藏
    pwd2set *p2 = new pwd2set();

    connect(p2,&pwd2set::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
    connect(p2,&pwd2set::sendpwd2,this,&manager::set_pwd2);//修改密码
    p2->get_pwd2(pwd2);//将原密码传给修改密码的窗口，用于验证
    p2->show();

}

//修改RFID密码
void manager::on_rfid_clicked()
{
    this->hide();//主界面隐藏
    change_rfid * r1 = new change_rfid();

    connect(r1,&change_rfid::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
    connect(r1,&change_rfid::sendpwd1,this,&manager::set_pwd1);//修改密码
    r1->get_pwd1(pwd1);//将原密码传给修改密码的窗口，用于验证
    r1->show();
}

//修改指纹
void manager::on_finger_clicked()
{
    this->hide();//主界面隐藏
    change_as608 * c1 = new change_as608();

    connect(c1,&change_as608::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
    c1->show();
}

void manager::on_exit1_clicked()
{

    emit sendsignal();
    this->close();
}

manager::~manager()
{
    delete ui;
}





