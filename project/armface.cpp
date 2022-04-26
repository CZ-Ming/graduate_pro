#include "armface.h"
#include "ui_armface.h"

#include <QBitmap>
#include <QPainter>
#include <QLine>
#include <QDebug>
#include <QMessageBox>
#include <opencv2/imgproc/types_c.h>



ArmFace::ArmFace(QWidget *parent) :QMainWindow(parent),ui(new Ui::ArmFace)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存

    thread = new CameraThread(this);//创建摄像头线程
    printf("gouzao%d\n",Socket_fd);

    udpconflag =  false;
    thread_flag =0;//摄像头关闭为 0
    locknum =0;


    this->setStyleSheet("QMainWindow{ background-color:rgb(218, 189, 165);}"); //设置颜色32, 54, 62
    ui->openbt->setStyleSheet("border-image:url(./face1.png)");     //设置开启人脸识别按钮图片
    ui->pushButton->setStyleSheet("border-image:url(./close.png)"); //设置关闭人脸识别按钮图片
    ui->cameraopen->setStyleSheet("border-image:url(./camera2.png)");//设置开启视频监控按钮图片
    ui->cameraclose->setStyleSheet("border-image:url(./close.png)");//设置关闭视频监控按钮图片

    show_lock(LOCKIMG);//显示门锁为锁定图
    QPixmap pixmap(LABELIMG);//视频框标签显示的图片
    pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->label->setScaledContents(true);
    ui->label->setPixmap(pixmap);//标签显示图片


    //连接信号和槽 如果摄像头线程发送图片过来  则显示在label标签上
    QObject::connect(thread,&CameraThread::send_image,this,[&](Mat cap1){
        cvtColor(cap1,cap1,CV_BGR2RGB);
        QImage image(cap1.data, cap1.cols, cap1.rows, cap1.step1() , QImage::Format_RGB888);
        QPixmap mmp = QPixmap::fromImage(image);
        mmp = mmp.scaled(ui->label->size());
        ui->label->setPixmap(mmp);
    });
    QObject::connect(thread,&CameraThread::sendfaceresult,this,[&](bool aflag){
        if(aflag)
            show_lock(UNLOCKIMG);//显示门锁为开锁图
    });


    //本线程发送信号结束摄像头线程
    QObject::connect(this,&ArmFace::send_flag,thread,&CameraThread::set_flag);
    QObject::connect(this,&ArmFace::send_udpflag,thread,&CameraThread::set_udpflag);
    QObject::connect(this,&ArmFace::send_faceflag,thread,&CameraThread::set_faceflag);

    QObject::connect(thread,&CameraThread::sendudpflag,this,[&](bool flag){
        udpconflag = flag;
    });

    QObject::connect(&locktimer,&QTimer::timeout,this,&ArmFace::lockrun);//定时器每1s连接一次UDP
    locktimer.start(1000);
}

ArmFace::~ArmFace()                                                         //析构函数
{
    delete ui;
}

void ArmFace::lockrun()
{
    locknum++;
    if(locknum == 5)
    {
        show_lock(LOCKIMG);//显示门锁为锁定图
        locknum =0;
    }
}

void ArmFace::get_socket(int socket)
{
    this->Socket_fd = socket;
}

//显示锁门图片 关锁LOCKIMG  开锁UNLOCKIMG
 void ArmFace::show_lock(const char * path)
 {
     QPixmap pixmap(path);//打开显示的图片
     //图片大小自适应标签
     pixmap.scaled(ui->label_3->size(), Qt::KeepAspectRatio);
     ui->label_3->setScaledContents(true);
     ui->label_3->setPixmap(pixmap);//标签显示图片
 }


 //退出
 void ArmFace::on_pushButton_2_clicked()
 {
     if(thread_flag != 0)
         QMessageBox::warning(this,"提示","请先停止摄像头数据采集",QMessageBox::Ok);
     else
     {
         emit sendtopsignal();
         this->close();
     }
 }


//按键按下人脸识别
void ArmFace::on_openbt_clicked()
{
    ui->openbt->setStyleSheet("border-image:url(./face.png)");
    ui->pushButton->setStyleSheet("border-image:url(./close1.png)");
    if(thread_flag == 0)
    {
        thread->start();// 启动摄像头线程
        thread_flag = 1;
    }
    if(thread_flag==2)//已经被监控开了
    {
        thread_flag = 3;
    }
    emit send_faceflag(true);//启动人脸识别
}


//按键按下停止人脸识别
void ArmFace::on_pushButton_clicked()
{

    ui->openbt->setStyleSheet("border-image:url(./face1.png)");
    ui->pushButton->setStyleSheet("border-image:url(./close.png)");
    if(thread_flag == 1)
    {
        thread_flag = 0;
        emit send_flag();//发送信号结束线程
    }
    if(thread_flag == 3)
     {
        thread_flag =2;
     }
    emit send_faceflag(false);//发送信号结束线程
}

//按键按下传输数据
void ArmFace::on_cameraopen_clicked()
{
    ui->cameraopen->setStyleSheet("border-image:url(./camera1.png)");
    ui->cameraclose->setStyleSheet("border-image:url(./close1.png)");

    if(thread_flag == 0)
    {
        thread->start();// 启动摄像头线程
        thread_flag = 2;
    }
    if(thread_flag==1)//已经被人脸开了
    {
        thread_flag = 3;
    }
    if(udpconflag == false)
    {
        thread->get_socket(Socket_fd);
        printf("open %d\n",Socket_fd);
        thread->camtimerstart();// 启动udp连接
    }
    else
        emit send_udpflag(true);

}
//按键按下停止传输数据
void ArmFace::on_cameraclose_clicked()
{
   ui->cameraopen->setStyleSheet("border-image:url(./camera2.png)");
   ui->cameraclose->setStyleSheet("border-image:url(./close.png)");

   if(thread_flag == 2)
    {
       thread_flag =0;
       emit send_flag();//发送信号结束线程
    }
   if(thread_flag == 3)
    {
       thread_flag =1;
    }

   if(udpconflag == false)
       thread->camtimerend();// 结束udp连接定时器
   else
       emit send_udpflag(false);
}




