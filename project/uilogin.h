#ifndef UILOGIN_H
#define UILOGIN_H

#include <QDialog>

namespace Ui {
class UiLogin;
}

class UiLogin : public QDialog
{
    Q_OBJECT

public:
    explicit UiLogin(QWidget *parent = nullptr);
    ~UiLogin();
    void get_pwd_sudo(int pwd);

private slots:
    void on_n1_clicked();
    void on_n2_clicked();
    void on_n3_clicked();
    void on_n0_clicked();
    void on_n4_clicked();
    void on_n5_clicked();
    void on_n6_clicked();
    void on_login_clicked();
    void on_n7_clicked();
    void on_n8_clicked();
    void on_n9_clicked();
    void on_exit1_clicked();
    void on_ncl_clicked();

private:
    Ui::UiLogin *ui;
    int pwd;
    int pwd_sudo;

};

#endif // UILOGIN_H
