#include "main_interface.h"
#include "ui_main_interface.h"
#include <qdebug.h>
//菜单界面，有管理员和开锁模式


main_interface::main_interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_interface)
{
    ui->setupUi(this);

    QPixmap pixmap("../ui/main.png");//打开显示的图片
    pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->label->setScaledContents(true);
    ui->label->setPixmap(pixmap);//标签显示图片
    ui->manage->setStyleSheet("border-image:url(../ui/m1.png)");
    ui->lock->setStyleSheet("border-image:url(../ui/l1.png)");

    thread = new CameraThread(this);//创建摄像头线程
    udpsocket = new QUdpSocket();

    const quint16 LOCAL_PORT = 2234;// 本机端口
    const QString LOCAL_HostAddress="192.168.0.108";// 本机IP地址
    udpsocket->bind(QHostAddress(LOCAL_HostAddress), LOCAL_PORT);//UDP绑定ip和端口


    pwd1 = 666666;//卡密码
    pwd2 = 666666;//数字密码
    pwd_sudo = 666666;//管理员密码

    connect(&sec_3,&QTimer::timeout,this,&main_interface::clock_3secrun);    //3s后自动进入解锁界面
    connect(this,&main_interface::send_udpflag,thread,&CameraThread::set_udpflag);//UDP连接成功，发送信号提醒摄像头线程发送数据
    connect(udpsocket, SIGNAL(readyRead()), this, SLOT(receive()));//UDP接收到信号则处理

    sec_3.start(1000);//启动3s进入界面定时器
    thread->start();  //启动摄像头线程

}


void main_interface::receive()
{
    QHostAddress targetaddr;//ip
    quint16 targetport;//端口号
    while(udpsocket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpsocket->pendingDatagramSize());
        udpsocket->readDatagram(data.data(), data.size(),&targetaddr,&targetport);

        if(strcmp(data.data(),"GET_VIDEO")==0)
        {
            thread->get_udp_msg(udpsocket,targetaddr,targetport);
            volatile int i =3000;
            while(i--);
            emit send_udpflag(true);
        }
    }
}



//设置rfid密码
void main_interface::set_pwd1(int num)
{
    pwd1 = num;
}
//设置数字密码
void main_interface::set_pwd2(int num)
{
    pwd2 = num;
}

//管理员模式
void main_interface::on_manage_clicked()
{

    UiLogin w;
    w.get_pwd_sudo(pwd_sudo);

    if(QDialog::Accepted==w.exec()){
        this->hide();//主界面隐藏
        manager *manger1 = new manager();
        connect(manger1,&manager::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
        connect(manger1,&manager::sendpwd1,this,&main_interface::set_pwd1);//设置rfid密码
        connect(manger1,&manager::sendpwd2,this,&main_interface::set_pwd2);//设置数字密码
        manger1->getpwd2(pwd2);//传递密码
        manger1->getpwd1(pwd1);//传递密码
        manger1->show();//显示窗口
    }
}

//启动3s后自动进入开锁模式
void main_interface::clock_3secrun()
{
    sec_3.stop();
    this->hide();//主界面隐藏

    open_interface *open_interface1 = new open_interface(thread);
    connect(open_interface1,&open_interface::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
    open_interface1->get_pwd1(pwd1);//传递密码
    open_interface1->get_pwd2(pwd2);//传递密码
    open_interface1->show();
}


//按钮进入开锁模式
void main_interface::on_lock_clicked()
{
    this->hide();//主界面隐藏
    open_interface *open_interface1 = new open_interface(thread);
    connect(open_interface1,&open_interface::sendsignal,this,[&](){this->show();});//关闭子窗口重现父窗口
    open_interface1->get_pwd1(pwd1);//传递密码
    open_interface1->get_pwd2(pwd2);//传递密码
    open_interface1->show();
}



main_interface::~main_interface()
{
    delete ui;
}
