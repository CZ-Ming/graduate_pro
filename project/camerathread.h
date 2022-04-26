#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QMutex>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "face.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QUdpSocket>
#include <QPixmap>
#include "jpeglib.h"
#include <QTimer>
#include <QUdpSocket>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>

using namespace cv;

#define WIDTH 640//320
#define HEIGHT 480//240
#define OUTPUT_BUF_SIZE  4096

#define UDPPORT 8888
#define SERVERIP "192.168.0.255"


typedef struct
{
      char* start;
      size_t length;
} buffer_t;

typedef struct {

    struct jpeg_destination_mgr pub;
    JOCTET * buffer;
    unsigned char *outbuffer;
    int outbuffer_size;
    unsigned char *outbuffer_cursor;
    int *written;

}mjpg_destination_mgr;
typedef mjpg_destination_mgr *mjpg_dest_ptr;

class CameraThread : public QThread
{
    Q_OBJECT

public:
    explicit CameraThread(QObject *parent=nullptr);
    ~CameraThread();

    void run();//重写线程函数
    void get_udp_msg(QUdpSocket *udpsocket,QHostAddress targetaddr,quint16 targetport);


private:
    void camera_init();//摄像头初始化
    void camera_release();//摄像头释放
    int yuyv2rgb(int y, int u, int v);
    int yuyv2rgb0(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height);

    int Predict(Mat src_image);//人脸预测函数
    int compress_yuyv_to_jpeg(unsigned char *buf, unsigned char *buffer, int size, int quality);
    void dest_buffer(j_compress_ptr cinfo, unsigned char *buffer, int size, int *written);

    buffer_t buffer[4];
    buffer_t current;//当前取出一帧
    int camera_fd;
    unsigned int sign3 = 0;

    Mat cap,gray;//人脸识别存储容器
    CascadeClassifier cascade;
    Ptr<face::FaceRecognizer> model;
    bool face_flag;

    bool runflag;

    QUdpSocket *udpsocket;
    QHostAddress targetaddr;//ip
    quint16 targetport;//端口号
    bool udp_flag;



signals:
    void send_image(Mat mmm);
    void send_res();

public slots:
    void set_runflag(bool flag);//获取是否结束线程
    void set_udpflag(bool flag);
    void set_faceflag(bool flag);


};






METHODDEF(void) init_destination(j_compress_ptr cinfo)
{
    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    dest->buffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE, OUTPUT_BUF_SIZE * sizeof(JOCTET));
    *(dest->written) = 0;
    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

}

METHODDEF(boolean) empty_output_buffer(j_compress_ptr cinfo)
{

    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    memcpy(dest->outbuffer_cursor, dest->buffer, OUTPUT_BUF_SIZE);
    dest->outbuffer_cursor += OUTPUT_BUF_SIZE;
    *(dest->written) += OUTPUT_BUF_SIZE;
    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

    return TRUE;

}

METHODDEF(void) term_destination(j_compress_ptr cinfo)
{
    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;
    /* Write any data remaining in the buffer */
    memcpy(dest->outbuffer_cursor, dest->buffer, datacount);
    dest->outbuffer_cursor += datacount;
    *(dest->written) += datacount;

}




#endif // CAMERATHREAD_H
