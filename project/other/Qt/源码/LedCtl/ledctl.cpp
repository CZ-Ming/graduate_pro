#include "ledctl.h"
#include "ui_ledctl.h"

extern"C"
{
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <unistd.h>
   #include <stdlib.h>
}
LedCtl::LedCtl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LedCtl)
{
    ui->setupUi(this);
    //打开led设备文件
    fd = ::open("/dev/led_drv", O_WRONLY);
}

LedCtl::~LedCtl()
{
    delete ui;
    ::close(fd);
}

void LedCtl::on_led1Bt_clicked()
{
    if(ui->led1Bt->text() == "open")
    {
        ui->led1Bt->setText("close");
        char buf[2];
        buf[1]=8; buf[0]=1; //led2 on
        int ret = write(fd,buf,2);

    }else
    {
        ui->led1Bt->setText("open");
        char buf[2];
        buf[1]=8; buf[0]=0; //led2 on
        int ret = write(fd,buf,2);
    }
}

void LedCtl::on_led2Bt_clicked()
{
    if(ui->led2Bt->text() == "open")
    {
        ui->led2Bt->setText("close");
        char buf[2];
        buf[1]=9; buf[0]=1; //led2 on
        int ret = write(fd,buf,2);

    }else
    {
        ui->led2Bt->setText("open");
        char buf[2];
        buf[1]=9; buf[0]=0; //led2 on
        int ret = write(fd,buf,2);
    }
}
