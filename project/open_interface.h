#ifndef OPEN_INTERFACE_H
#define OPEN_INTERFACE_H

#include <QWidget>
#include <QMessageBox>
#include <QMetaType>
#include <QThread>
#include <sys/ioctl.h>
#include <QDateTime>
#include <unistd.h>//使用::close关闭文件描述符
#include <QTimer>
#include "as608.h"
#include "camerathread.h"
#include "motorthread.h"

#define CMD_RFID_WR     _IOW('R',0,unsigned int)
#define CMD_RFID_RD     _IOR('R',0,unsigned int)
#define CMD_RFID_RDID   _IOR('R',1,unsigned int)


#include <iostream>



namespace Ui {
class open_interface;
}

class open_interface : public QWidget
{
    Q_OBJECT

public:
    explicit open_interface(CameraThread *thread,QWidget *parent = nullptr);
    ~open_interface();
    void startfprun();//指纹初始化
    void findfprun();//指纹查找
    void initrun();//rfid初始化
    void startrdrun();//rfid验卡
    void buzzerrun();//蜂鸣器
    void motorrun();
    void get_pwd1(int num);//rfid
    void get_pwd2(int num);//密码

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息
    void sendrunflag(bool flag);
    void sendfaceflag(bool flag);
    void sendfuncflag(int flag);
    void sendmotor_runflag(bool flag);

private slots:
    void on_clo_clicked();
    void on_n1_clicked();
    void on_n2_clicked();
    void on_n3_clicked();
    void on_n0_clicked();
    void on_n4_clicked();
    void on_n5_clicked();
    void on_n6_clicked();
    void on_ncl_clicked();
    void on_n7_clicked();
    void on_n8_clicked();
    void on_n9_clicked();
    void on_nok_clicked();
    void set_faceres();




private:
    Ui::open_interface *ui;

    int pwd;//输入密码
    int pwd2[6];//定义密码
    int pwd1[6]; //开锁密码 666666
    bool uart_flag;
    int rfid_fd;//RFID文件描述符   未启动RFID 值为-1
    int fault_num;
    bool face_open;
    bool fgrunflag;

    as608 as1;
    u16 ValidN;//模块内有效指纹个数
    SysPara AS608Para;//指纹模块AS608参数

    QTimer startfptimer;//启动指纹模块
    QTimer findfptimer;//指纹验证
    QTimer rfidinittimer;// 初始化RFID读卡验证
    QTimer startrdtimer;//启动RFID读卡验证
    QTimer buzzertimer;
    QTimer motortimer;
    CameraThread *thread;//摄像头采集线程类
    motorthread *motorthread1;



};

#endif // OPEN_INTERFACE_H
