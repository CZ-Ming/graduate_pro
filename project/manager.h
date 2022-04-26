#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <iostream>

#include "pwd2set.h"
#include "change_as608.h"
#include "change_rfid.h"

namespace Ui {
class manager;
}

class manager : public QWidget
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();
    void getpwd2(int pwd2);
    void getpwd1(int pwd1);

private slots:
    void on_finger_clicked();
    void on_pass_clicked();
    void on_rfid_clicked();
    void set_pwd2(int pwd2);
    void set_pwd1(int pwd1);
    void on_exit1_clicked();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息
    void sendpwd1(int num);
    void sendpwd2(int num);

private:
    Ui::manager *ui;
    int pwd2;
    int pwd1;

};

#endif // MANAGER_H
