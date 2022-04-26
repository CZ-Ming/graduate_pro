#include "motorthread.h"
#include <qdebug.h>
motorthread::motorthread(QObject *parent):QThread(parent)
{

    connect(&timer1,&QTimer::timeout,this,&motorthread::timerun);

    func_flag =0;
    init_flag =0;
    run_flag = true;
    timer1.start(300);

}


//线程函数
void motorthread::timerun()
{
    if(init_flag==0)
    {
        buzzer_fd = open("/dev/beep", O_RDWR);            //打开设备，成功返回0
        if(buzzer_fd<0){
            perror("open:");
            return ;
        }
        init_flag =1;
    }

    if(init_flag==1)
    {
        motor_fd = open("/dev/motor", O_RDWR);            //打开设备，成功返回0
        if(motor_fd<0){
            perror("open:");
            return ;
        }
        init_flag =2;
    }
    timer1.stop();
    emit finish_init();
    qDebug()<<"motor finish";

}

void motorthread::Sleep(int msec)
{
    qint64 dieTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    while( QDateTime::currentDateTime().toMSecsSinceEpoch()-dieTime < msec )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        QThread::msleep(1);
    }

}
void motorthread::set_func_flag(int flag)
{
    this->func_flag = flag;
    qDebug()<<"set_func_flag"<<flag;
}

void motorthread::set_run_flag(bool flag)
{
    this->run_flag = flag;
}

//线程函数
void motorthread::run()
{
    qDebug()<<"motor run";
    while(1)
    {

        if(!run_flag)break;
        switch(func_flag)
        {
            case 1://开门
            {
                qDebug()<<"motor open";
                int i =40;
                while(i--)
                {
                    ioctl(motor_fd, CDM_MOTOR_HIGH, 1);                //BUZZER off
                    Sleep(3);
                    ioctl(motor_fd, CDM_MOTOR_LOW, 1);                //BUZZER off
                    Sleep(17);
                }
                func_flag =0;
            }break;

            case 2://关门
            {
                int i =20;
                while(i--)
                {
                    ioctl(motor_fd, CDM_MOTOR_CLOSE, 1);                //BUZZER off
                }
                func_flag =0;
            }break;

            case 3://蜂鸣器响
            {
                ioctl(buzzer_fd, 0, 1);
                func_flag =0;
            }break;

            case 4://蜂鸣器不响
            {
                ioctl(buzzer_fd, 1, 1);
                func_flag =0;
            }break;
        }
    msleep(10);
    }
    delete this;
}
//析构函数
motorthread::~motorthread()
{
    if(buzzer_fd !=-1)
        ::close(buzzer_fd);
    if(motor_fd !=-1)
        ::close(motor_fd);
}





