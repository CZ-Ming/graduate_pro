#include "open_interface.h"
#include "ui_open_interface.h"
#include <qdebug.h>

using namespace std;


open_interface::open_interface(CameraThread *thread,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::open_interface)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存
    qRegisterMetaType< Mat >("Mat");

    QPixmap pixmap("../ui/laberpassword.png");//打开显示的图片
    pixmap.scaled(ui->word->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->word->setScaledContents(true);
    ui->word->setPixmap(pixmap);//标签显示图片
    ui->back->setStyleSheet("border-image:url(../ui/back.png)");
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
    ui->clo->setStyleSheet("border-image:url(../ui/clo.png)");

//摄像头线程
    this->thread = thread;
    this->motorthread1 = new motorthread();
    connect(motorthread1,&motorthread::finish_init,this,[&](){motorthread1->start();});   //定时器，用于连接指纹模块
    connect(this,&open_interface::sendfuncflag,motorthread1,&motorthread::set_func_flag);


// 指纹
    uart_flag =false;
    fgrunflag = false;
    connect(&startfptimer,&QTimer::timeout,this,&open_interface::startfprun);   //定时器，用于连接指纹模块
    connect(&findfptimer,&QTimer::timeout,this,&open_interface::findfprun);     //定时器，用于指纹验证

//rfid
    connect(&startrdtimer,&QTimer::timeout,this,&open_interface::startrdrun);   //定时器，用于启动rfid
    connect(&rfidinittimer,&QTimer::timeout,this,&open_interface::initrun);     //定时器，用于rfid读卡

// 解锁和报警
    fault_num =0;
    connect(&motortimer,&QTimer::timeout,this,&open_interface::motorrun);
    connect(&buzzertimer,&QTimer::timeout,this,&open_interface::buzzerrun);

//当前输入的密码
    pwd =0;

//人脸识别
    face_open = false;
    //连接信号和槽 如果摄像头线程发送图片过来  则显示在label标签上
    QObject::connect(thread,&CameraThread::send_image,this,[&](Mat cap1){
        cvtColor(cap1,cap1,CV_BGR2RGB);
        QImage image(cap1.data, cap1.cols, cap1.rows, cap1.step1() , QImage::Format_RGB888);
        QPixmap mmp = QPixmap::fromImage(image);
        mmp = mmp.scaled(ui->face->size());
        ui->face->setScaledContents(true);
        ui->face->setPixmap(mmp);
    });

    connect(thread,&CameraThread::send_res,this,&open_interface::set_faceres);//返回识别成功信号
    connect(this,&open_interface::sendfaceflag,thread,&CameraThread::set_faceflag);//摄像头启动人脸识别

    rfidinittimer.start(500);//初始化RFID定时器
    startfptimer.start(300);//初始化指纹定时器
//    buzzertimer.start(2000);//启动蜂鸣器定时器

    emit sendfaceflag(true);

}

//初始化指纹
void open_interface::startfprun()
{
    if(!uart_flag)
    {
        int ret = as1.serial_init(DEV_PATH,B57600);//串口初始化
        if(ret<0)
        {
            perror("serial_init err");
            return ;
        }
        uart_flag = true;
    }

    if(as1.PS_HandShake(&AS608Addr))//与AS608模块握手
        return ;//没有连接上则退出本次定时器
    as1.PS_ValidTempleteNum(&ValidN);//读库指纹个数
    as1.PS_ReadSysPara(&AS608Para);//读参数
    startfptimer.stop();// 停止初始化指纹定时器
    findfptimer.start(1000);//开启指纹验证定时器
    fgrunflag =true;
}


//验证指纹是否可以开门
void open_interface::findfprun()
{
    u8 ensure=as1.PS_GetImage();
    if(ensure==0x00)//获取图像成功
    {
         qDebug()<<"bug(2)";
        ensure=as1.PS_GenChar(CharBuffer1);
        if(ensure==0x00) //生成特征成功
        {
            SearchResult seach;
            ensure=as1.PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
            if(ensure==0x00)//搜索成功
            {
                fault_num=0;
                emit sendfuncflag(1);
                motortimer.start(5000);
                findfptimer.stop();//开启指纹验证定时器
                fgrunflag =false;
            }
            else
                fault_num++;
        }
    }
}

//rfid密码
void open_interface::get_pwd1(int num)
{
    pwd1[0] = num/100000;
    pwd1[1] = num%100000/10000;
    pwd1[2] = num%10000/1000;
    pwd1[3] = num%1000/100;
    pwd1[4] = num%100/10;
    pwd1[5] = num%10;
}

//初始化RFID
void open_interface::initrun()
{
    rfid_fd = open("/dev/mfrc522_dev",O_RDWR);//打开RFID驱动程序
    if(rfid_fd<0)
    {
        perror("mfrc522 open err!");
        return ;
    }

    rfidinittimer.stop();//关闭初始化
    startrdtimer.start(500);//开启RFID读卡定时器
}

//验证RFID卡是否可以开锁
void open_interface::startrdrun()
{

    char buf[32] ={0};
    ioctl(rfid_fd,CMD_RFID_RDID,buf);//读取RFID卡ID

    //在没有RFID卡插入时卡序列为1 2 3 4， 由驱动程序决定
    if(buf[0] ==0 && buf[1] ==1 && buf[2] ==2 && buf[3] ==3 && buf[4] ==4);
    else
    {
        ioctl(rfid_fd,CMD_RFID_RD,buf);//读取RFID卡存储的密码
        //正确开门密码为666666
        if(buf[0] ==pwd1[0] && buf[1] ==pwd1[1] && buf[2] ==pwd1[2] &&
                buf[3] ==pwd1[3] && buf[4] ==pwd1[4] && buf[5] ==pwd1[5])
        {
            fault_num =0;
            emit sendfuncflag(1);
            motortimer.start(5000);
        }
        else
            fault_num++;

    }
}

//5s后自动上锁
void open_interface::motorrun()
{
    motortimer.stop();
    emit sendfuncflag(2);
    face_open = false;
    qDebug()<<"sendfuncflag(2)";
    if(!fgrunflag)
    {
        findfptimer.start(1000);//开启指纹验证定时器
        fgrunflag =true;
    }

}

//密码
void open_interface::get_pwd2(int num)
{
    pwd2[0] = num/100000;
    pwd2[1] = num%100000/10000;
    pwd2[2] = num%10000/1000;
    pwd2[3] = num%1000/100;
    pwd2[4] = num%100/10;
    pwd2[5] = num%10;
}

//密码开门
void open_interface::on_nok_clicked()
{

    int pwd3[6]; //开锁密码 666666
    pwd3[0] = pwd/100000;
    pwd3[1] = pwd%100000/10000;
    pwd3[2] = pwd%10000/1000;
    pwd3[3] = pwd%1000/100;
    pwd3[4] = pwd%100/10;
    pwd3[5] = pwd%10;
    if(pwd3[0] ==pwd2[0] && pwd3[1] ==pwd2[1] && pwd3[2] ==pwd2[2] &&
            pwd3[3] ==pwd2[3] && pwd3[4] ==pwd2[4] && pwd3[5] ==pwd2[5])
    {
        fault_num =0;
        emit sendfuncflag(1);
        motortimer.start(5000);
        qDebug()<<"sendfuncflag(1)";
    }
    else
        fault_num++;
    on_ncl_clicked();
}

//蜂鸣器控制
void open_interface::buzzerrun()
{
    if(fault_num>5)
        emit sendfuncflag(3);
    else
        emit sendfuncflag(4);
}

//人脸解锁
void open_interface::set_faceres()
{
    if(!face_open)
    {
        emit sendfuncflag(1);
        motortimer.start(5000);
        face_open = true;
    }
}

//退出当前界面
void open_interface::on_clo_clicked()
{
//    volatile int i =60000;
    buzzertimer.stop();
    motortimer.stop();
    startfptimer.stop();
    findfptimer.stop();
    startrdtimer.stop();
    rfidinittimer.stop();

    emit sendfuncflag(2);
    emit sendfuncflag(4);
    emit sendfaceflag(false);
    emit sendmotor_runflag(false);
    as1.serial_close();
    if(rfid_fd !=-1)
        ::close(rfid_fd);
//    while(i--);
//    delete motorthread1;
    emit sendsignal();
    this->close();
}



//析构函数
open_interface::~open_interface()
{
    delete ui;
}


//数字键盘
void open_interface::on_ncl_clicked()
{
    pwd=0;
    ui->lcdNumber->display("0");//清空lcd数字显示屏幕
}

void open_interface::on_n0_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+0;
         ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n1_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+1;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n2_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+2;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n3_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+3;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n4_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+4;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n5_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+5;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n6_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+6;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n7_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+7;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n8_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+8;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void open_interface::on_n9_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+9;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}


