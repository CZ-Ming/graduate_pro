#ifndef LEDCTL_H
#define LEDCTL_H

#include <QMainWindow>

namespace Ui {
class LedCtl;
}

class LedCtl : public QMainWindow
{
    Q_OBJECT

public:
    explicit LedCtl(QWidget *parent = 0);
    ~LedCtl();

private slots:
    void on_led1Bt_clicked();

    void on_led2Bt_clicked();

private:
    Ui::LedCtl *ui;
    int fd ;//文件描述符
};

#endif // LEDCTL_H
