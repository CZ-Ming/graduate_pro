#ifndef ARMFACE_H
#define ARMFACE_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "face.hpp"
#include <fstream>
#include <sstream>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "camerathread.h"
#include <QThread>
#include "topmainwindow.h"

using namespace cv;



#define LOCKIMG     "./1.png"
#define UNLOCKIMG   "./2.png"
#define LABELIMG    "./2.bmp"



namespace Ui {
class ArmFace;
}

class ArmFace : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmFace(QWidget *parent = nullptr);
    ~ArmFace();

    void show_lock(const char * path);
    void get_socket(int socket);

private slots:
    void on_openbt_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_cameraopen_clicked();

    void on_cameraclose_clicked();

private:
    Ui::ArmFace *ui;


    //摄像头采集线程类
    CameraThread *thread;
    int Socket_fd;

    bool  udpconflag;
    int   thread_flag; //摄像头关闭为0

    QTimer locktimer;
    int locknum;


protected slots:
    void lockrun();//定时器

signals:
    void send_flag();
    void send_udpflag(bool flag);
    void send_faceflag(bool flag);
    void sendtopsignal();

};

#endif // ARMFACE_H
