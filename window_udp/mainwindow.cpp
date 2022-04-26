#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Recv_Sock = new QUdpSocket();
    connect(Recv_Sock,SIGNAL(readyRead()),this,SLOT(Video_show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Video_show()
{
    //49657
    char data[65535];

    QHostAddress Addr;
    quint16 port;
    int ret; //接受收到图片大小

    ret = Recv_Sock->readDatagram(data,65535,&Addr,&port);
    ui->label->clear();
    pix.loadFromData((uchar *)data,ret);
    pix = pix.scaled(ui->label->width(),ui->label->height());


    QImage Qimg =pix.toImage();     //Qimage <--- pixmap

    Mat Mimg(Qimg.height(),Qimg.width(),CV_8UC4,(void*)Qimg.constBits(),Qimg.bytesPerLine());
    cvtColor(Mimg, Mimg, COLOR_BGRA2RGB);
    QImage img((const uchar*)Mimg.data,Mimg.cols,Mimg.rows,
                Mimg.cols*(Mimg.channels ()),QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

}



void MainWindow::on_pushButton_clicked()
{
    QHostAddress Addr;
    quint16 port;

    Addr = QHostAddress("192.168.0.108");
    port = 2234;
    Recv_Sock->writeDatagram("GET_VIDEO",10,Addr,port);


}

