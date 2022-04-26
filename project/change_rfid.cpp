#include "change_rfid.h"
#include "ui_change_rfid.h"

change_rfid::change_rfid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_rfid)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存

    QPixmap pixmap("../ui/back.png");//打开显示的图片
    pixmap.scaled(ui->back->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->back->setScaledContents(true);
    ui->back->setPixmap(pixmap);//标签显示图片

    ui->addexit->setStyleSheet("border-image:url(../ui/clo.png)");
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
    ui->card->setStyleSheet("border-image:url(../ui/card.png)");
    ui->password->setStyleSheet("border-image:url(../ui/password.png)");
    ui->label->setStyleSheet("color:rgb(255,255,255)");
    ui->label_2->setStyleSheet("color:rgb(255,255,255)");

    pwd = 0;
    connect(&startrdtimer,&QTimer::timeout,this,&change_rfid::startrdrun);//定时器，用于启动rfid读卡
    connect(&readtimer,&QTimer::timeout,this,&change_rfid::readrun);//定时器，每1s读取一次RFID卡
    startrdtimer.start(300);//启动初始化RFID模块定时器

}


void change_rfid::get_pwd1(int pwd1)
{
    this->pwd1 = pwd1;
}

void change_rfid::startrdrun()
{

    rfid_fd = open("/dev/mfrc522_dev",O_RDWR);//打开RFID驱动程序
    if(rfid_fd<0)
    {
        perror("mfrc522 open err!");
        return ;
    }
    startrdtimer.stop();//关闭初始化
    readtimer.start(1000);//开启RFID读卡定时器
}

void change_rfid::readrun()
{
    char buf[32] ={0};

    ioctl(rfid_fd,CMD_RFID_RDID,buf);//读取RFID卡ID

    //在没有RFID卡插入时卡序列为1 2 3 4， 由驱动程序决定
    if(buf[0] ==0 && buf[1] ==1 && buf[2] ==2 && buf[3] ==3 && buf[4] ==4);
    else
    {
        ui->rfidedit->append("卡号是:");
        sprintf(buf,"%d %d %d %d %d",buf[0],buf[1],buf[2],buf[3],buf[4]);
        ui->rfidedit->moveCursor(QTextCursor::End);//追加数据不换行
        ui->rfidedit->insertPlainText(buf);

        ui->rfidedit->append("卡内容:");
        ioctl(rfid_fd,CMD_RFID_RD,buf);//读取RFID卡内容
        sprintf(buf,"%x %x %x %x %x %x\n", buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
        ui->rfidedit->moveCursor(QTextCursor::End);//追加数据不换行
        ui->rfidedit->insertPlainText(buf);//在消息栏显示读取到RFID卡内容（密码）
    }

}

//点击确认按钮
void change_rfid::on_nok_clicked()
{
    if(pwd>99999)
    {
        char str[32] = {0};
        pwd1 = pwd;
        ui->rfidedit->append("6位密码保存成功");
        sprintf(str,"新密码为: %d\n",pwd1);
        ui->rfidedit->append(str);
        ui->rfidedit->append("请选择此密码具体用途。");
    }

    else
        QMessageBox::warning(this,"提示","输入密码位数不够6位",QMessageBox::Ok);
    on_ncl_clicked();
}

//修改卡内数据
void change_rfid::on_card_clicked()
{
    u8  card_writebuf[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    if(pwd1>99999)
    {
        char str[32] = {0};

        card_writebuf[0] = pwd1/100000;
        card_writebuf[1] = pwd1%100000/10000;
        card_writebuf[2] = pwd1%10000/1000;
        card_writebuf[3] = pwd1%1000/100;
        card_writebuf[4] = pwd1%100/10;
        card_writebuf[5] = pwd1%10;
        ioctl(rfid_fd,CMD_RFID_WR,card_writebuf);//向RFID卡写入  新密码

        ui->rfidedit->append("密码设置成功。");
        sprintf(str,"新密码为: %d\n",pwd1);
        ui->rfidedit->append(str);

    }
    else
        QMessageBox::warning(this,"提示"," 请先保存6位密码",QMessageBox::Ok);


}

//修改卡开门密码
void change_rfid::on_password_clicked()
{
    if(pwd1>99999)
         emit sendpwd1(pwd1);
    else
        QMessageBox::warning(this,"提示","请先保存6位密码",QMessageBox::Ok);

}


//退出
void change_rfid::on_addexit_clicked()
{
    startrdtimer.stop();
    readtimer.stop();

    if(rfid_fd !=-1)
        ::close(rfid_fd);
    emit sendsignal();
    this->close();
}




change_rfid::~change_rfid()
{
    delete ui;
}

//数字键盘
void change_rfid::on_ncl_clicked()
{
    pwd=0;
    ui->lcdNumber->display("0");//清空lcd数字显示屏幕
}

void change_rfid::on_n0_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+0;
         ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n1_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+1;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n2_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+2;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n3_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+3;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}



void change_rfid::on_n4_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+4;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n5_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+5;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n6_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+6;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}



void change_rfid::on_n7_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+7;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n8_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+8;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_rfid::on_n9_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+9;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}



