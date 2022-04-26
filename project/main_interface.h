#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H

#include <QMainWindow>
#include <QTimer>
#include <fcntl.h>
#include <iostream>
#include <QUdpSocket>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "open_interface.h"
#include "uilogin.h"
#include "manager.h"
#include "camerathread.h"



QT_BEGIN_NAMESPACE
namespace Ui { class main_interface; }
QT_END_NAMESPACE

class main_interface : public QMainWindow
{
    Q_OBJECT

public:
    main_interface(QWidget *parent = nullptr);
    ~main_interface();


public slots:
    void set_pwd1(int num);
    void set_pwd2(int num);
    void receive();

private slots:
    void clock_3secrun();
    void on_lock_clicked();
    void on_manage_clicked();

signals:
    void send_udpflag(bool flag);

private:
    Ui::main_interface *ui;

    int pwd1;//rfid卡密码
    int pwd2;//数字密码
    int pwd_sudo;//数字密码

    QTimer sec_3;//3s自动进入解锁模式
    CameraThread *thread;//摄像头采集线程类
    QUdpSocket *udpsocket;//UDP通信套接字

};
#endif // MAIN_INTERFACE_H
