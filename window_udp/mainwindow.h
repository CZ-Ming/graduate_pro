#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QPixmap>
#include "opencv2/opencv.hpp"
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Video_show();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

    QUdpSocket *Recv_Sock;
    QPixmap pix;




};

#endif // MAINWINDOW_H
