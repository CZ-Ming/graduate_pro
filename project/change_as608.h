#ifndef CHANGE_AS608_H
#define CHANGE_AS608_H

#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include "as608.h"


namespace Ui {
class change_as608;
}

class change_as608 : public QWidget
{
    Q_OBJECT

public:
    explicit change_as608(QWidget *parent = nullptr);
    ~change_as608();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消

private slots:
    void on_addexit_clicked();
    void on_addfp_clicked();
    void on_delfp_clicked();
    void on_findfp_clicked();
    void on_n0_clicked();
    void on_n1_clicked();
    void on_n2_clicked();
    void on_n3_clicked();
    void on_n4_clicked();
    void on_n5_clicked();
    void on_n6_clicked();
    void on_ncl_clicked();
    void on_n7_clicked();
    void on_n8_clicked();
    void on_n9_clicked();
    void on_nok_clicked();

protected slots:
    void run();//指纹录制定时器
    void frun();//验证指纹
    void srun();//初始化指纹模块
    void drun();//删除


private:
    Ui::change_as608 *ui;

    as608 add_as1;
    bool uart_flag;
    SysPara AS608Para;
    u16 ValidN;//模块内有效指纹个

    int pwd;
    int pwd_id;
    bool pwd_flag;
    int degree;//读取10次指纹，测到则退
    int processnum;//录指纹的四验证

    //定时器ID
    QTimer mtimer;//录指
    QTimer ftimer;//查指
    QTimer stimer;//启动
    QTimer dtimer;//删除

};

#endif // CHANGE_AS608_H
