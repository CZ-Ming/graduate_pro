#ifndef CHANGE_RFID_H
#define CHANGE_RFID_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include<unistd.h>//使用::close关闭文件描述符
#include "open_interface.h"

namespace Ui {
class change_rfid;
}

class change_rfid : public QWidget
{
    Q_OBJECT

public:
    explicit change_rfid(QWidget *parent = nullptr);
    ~change_rfid();
    void get_pwd1(int pwd1);

protected slots:
    void readrun();
    void startrdrun();

private slots:
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
    void on_addexit_clicked();
    void on_card_clicked();
    void on_password_clicked();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消
    void sendpwd1(int pwd1);//这个函数用户向主界面通知关闭的消息
private:
    Ui::change_rfid *ui;
    int pwd;
    int pwd1;
    int rfid_fd;//RFID文件描述符
    QTimer readtimer;//读RFID卡定时器
    QTimer startrdtimer;//读RFID卡定时器

};

#endif // CHANGE_RFID_H
