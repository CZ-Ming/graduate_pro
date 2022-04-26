#ifndef PWD2SET_H
#define PWD2SET_H

#include <QWidget>

namespace Ui {
class pwd2set;
}

class pwd2set : public QWidget
{
    Q_OBJECT

public:
    explicit pwd2set(QWidget *parent = nullptr);
    ~pwd2set();
    void get_pwd2(int pwd2);

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
    void on_check_clicked();
    void on_state_clicked();
    void on_exit1_clicked();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息
    void sendpwd2(int pwd2);//这个函数用户向主界面通知关闭的消息

private:
    Ui::pwd2set *ui;
    int pwd;
    int pwd2;
    int flag;

};

#endif // PWD2SET_H
