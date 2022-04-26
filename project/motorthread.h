#ifndef MOTORTHREAD_H
#define MOTORTHREAD_H
#include <QThread>

#include <QWidget>
#include <QMessageBox>
#include <QThread>
#include <sys/ioctl.h>
#include <QDateTime>
#include<unistd.h>//使用::close关闭文件描述符
#include <QTimer>
#include <QCoreApplication>
#include <fcntl.h>

#define CDM_MOTOR_HIGH   	_IOW('L',0,unsigned long)
#define CDM_MOTOR_LOW  		_IOW('L',1,unsigned long)
#define CDM_MOTOR_CLOSE  	_IOW('L',2,unsigned long)

class motorthread: public QThread
{
    Q_OBJECT
public:

    explicit motorthread(QObject *parent=nullptr);
    ~motorthread();
    void run();//重写线程函数
    void timerun();
    void Sleep(int msec);

signals:
    void finish_init();

public slots:
    void set_func_flag(int flag);
    void set_run_flag(bool flag);

private:
    int buzzer_fd;
    int motor_fd;

    QTimer timer1;
    int init_flag;
    int func_flag;
    bool run_flag;

};

#endif // MOTORTHREAD_H
