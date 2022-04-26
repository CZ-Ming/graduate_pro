#include "camerathread.h"
#include <QMessageBox>


CameraThread::CameraThread(QObject *parent):QThread(parent)
{
    sign3 = 0;
    udp_flag = false;
    face_flag = false;
    camera_init();//初始化摄像头
    cascade.load("./new/haarcascade_frontalface_alt2.xml");//训练好的文件名称，放置在可执行文件同目录下
    model = face::FisherFaceRecognizer::create();
    model->read("./new/MyFaceFisherModel.xml"); //1.加载训练好的分类器
}

CameraThread::~CameraThread()
{
    camera_release();
}

void CameraThread::get_udp_msg(QUdpSocket *udpsocket,QHostAddress targetaddr,quint16 targetport)
{
    this->udpsocket = udpsocket;
    this->targetaddr = targetaddr;
    this->targetport = targetport;
}


void CameraThread::set_udpflag(bool flag)
{
    this->udp_flag = flag;
}
void CameraThread::set_faceflag(bool flag)
{
    this->face_flag = flag;
}


//获取是否结束线程
void CameraThread::set_runflag(bool flag)
{
    this->runflag = flag;
}
//线程函数
void CameraThread::run()
{

    char rgb[640*480*3];//RGB缓冲区
    runflag = false;
    int face_num =0;
    while(1)//采集数据
    {
        if(runflag)break;

        struct v4l2_buffer buf = {}; //出队
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        int res = ioctl(camera_fd,VIDIOC_DQBUF,&buf);
        if(res==-1)
            perror("ioctl DQBUF");

        memcpy(current.start,buffer[buf.index].start,buf.bytesused); //拷贝数据
        current.length = buf.bytesused;

        res = ioctl(camera_fd,VIDIOC_QBUF,&buf);//入队
        if(res==-1)
            perror("ioctl DQBUF");

        if(udp_flag)
        {

            unsigned char dest[buf.length+1]; //数据转换YUYV转JPEG
            int ret = compress_yuyv_to_jpeg((unsigned char *)current.start, dest,(WIDTH * HEIGHT), 80);
            QByteArray DataContent = QByteArray((char *)dest,ret);
            udpsocket->writeDatagram(DataContent, targetaddr, targetport);

        }
        if(face_flag)
        {

            yuyv2rgb0((unsigned char *)current.start,(unsigned char *)rgb,640,480);//YUYV转RGB
            QImage image = QImage((uchar *)rgb,640,480,QImage::Format_RGB888);//把采集的图像转换成QImage

           //把QImage转换成Mat
            cap = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
            cv::cvtColor(cap, cap, COLOR_RGB2BGR);

            //人脸识别
            std::vector<Rect> faces(0);//建立用于存放人脸的向量容器
            cvtColor(cap, gray, CV_RGB2GRAY);//测试图像必须为灰度图
            equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理
            cascade.detectMultiScale(gray, faces,1.1, 3, 0| CASCADE_DO_ROUGH_SEARCH,Size(200, 200), Size(400, 400));//检测人脸

            Mat* pImage_roi = new Mat[faces.size()];    //定义数组
            Mat face;
            Point text_lb;//文本写在的位置
            String str;//框出人脸
            unsigned int i=0;

            for ( i= 0; i < faces.size(); i++)
            {
                pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
                text_lb = Point((faces[i].x+faces[i].width)/2, faces[i].y);
                if (pImage_roi[i].empty())//没有人则跳过
                    continue;

                switch(Predict(pImage_roi[i]))//人脸预测
                {
                    case 42://根据标签输出结果
                    {
                        str = "czm";
                        face_num++;
                        if(face_num >=10)
                        {
                            face_num =0;
                            emit send_res();
                        }
                    }break;
                    case 42:
                    {
                        str = "crt";
                        face_num++;
                        if(face_num >=10)
                        {
                            face_num =0;
                            emit send_res();
                        }
                    }break;
                    default: str = "no";break;
                }

               //绘制边角
               cv::line(cap,Point(faces[i].x, faces[i].y),Point(faces[i].x+60,faces[i].y),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x, faces[i].y),Point(faces[i].x,faces[i].y+40),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x+faces[i].width-60, faces[i].y),Point(faces[i].x+faces[i].width,faces[i].y),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x+faces[i].width, faces[i].y),Point(faces[i].x+faces[i].width,faces[i].y+40),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x, faces[i].y+faces[i].height),Point(faces[i].x+60,faces[i].y+faces[i].height),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x, faces[i].y+faces[i].height-40),Point(faces[i].x,faces[i].y+faces[i].height),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x+faces[i].width-60, faces[i].y+faces[i].height),Point(faces[i].x+faces[i].width,faces[i].y+faces[i].height),Scalar(0,0,255),4);
               cv::line(cap,Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height-40),Point(faces[i].x+faces[i].width,faces[i].y+faces[i].height),Scalar(0,0,255),4);

               putText(cap, str, text_lb, FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255),4);//添加文字
            }
            delete[]pImage_roi;


            emit send_image(cap);//发送采集的QImage
        }
        //延时
        msleep(15);
    }
}



//初始化摄像头
void CameraThread::camera_init()
{
    //1.打开
    camera_fd = open("/dev/video7",O_RDWR);
    if(camera_fd==-1){
        perror("open");
        exit(-1);
    }

    //2.获取功能参数
    struct v4l2_capability cap;
    int res = ioctl(camera_fd,VIDIOC_QUERYCAP,&cap);
    if(res==-1){
        perror("ioctl CAP");
        exit(-1);
    }
    //判断是不是摄像头设备
    if(cap.capabilities&V4L2_CAP_VIDEO_CAPTURE){
        //是一个摄像头设备
        printf("is a capture device!\n");
    }

    //3.获取摄像头支持的格式
    struct v4l2_fmtdesc fmt;
    fmt.index = 0;//第一种格式
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;//摄像头格式

    while((res = ioctl(camera_fd,VIDIOC_ENUM_FMT,&fmt))==0){
        printf("pixelformat = %c%c%c%c,description = %s\n",fmt.pixelformat&0xff,(fmt.pixelformat>>8)&0xff,
                                    (fmt.pixelformat>>16)&0xff,(fmt.pixelformat>>24)&0xff,fmt.description);

        fmt.index++;
    }

    //4.设置采集通道
    int index = 0;//使用通道0
    ioctl(camera_fd,VIDIOC_S_INPUT,&index);

    //5.设置采集格式
    struct v4l2_format format = {};
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = 640;//像素宽度
    format.fmt.pix.height = 480;//像素高度
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;//YUYV格式
    format.fmt.pix.field = V4L2_FIELD_NONE;
    res = ioctl(camera_fd,VIDIOC_S_FMT,&format);
    if(res==-1){
        perror("ioctl S_FMT");
        exit(-1);
    }

    //6.申请缓冲区空间
    struct v4l2_requestbuffers req = {};
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    res = ioctl(camera_fd,VIDIOC_REQBUFS,&req);
    if(res==-1){
        perror("ioctl REQBUFS");
        exit(-1);
    }

    //7.分配，映射到用户空间，入队
    size_t i = 0,max_len = 0;
    for(i=0;i<4;i++){
        //分配空间
        struct v4l2_buffer buf = {};
        buf.index = i;//0~3
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        res = ioctl(camera_fd,VIDIOC_QUERYBUF,&buf);
        if(res==-1){
            perror("ioctl QUERYBUF");
            exit(-1);
        }

        //保存最大长度
        if(buf.length>max_len)
            max_len = buf.length;

        //映射
        buffer[i].length = buf.length;
        buffer[i].start = (char *)mmap(NULL,buf.length,PROT_WRITE|PROT_READ,MAP_SHARED,camera_fd,buf.m.offset);
        if(buffer[i].start==MAP_FAILED){
            perror("mmap");
            exit(-1);
        }

        //入队
        res = ioctl(camera_fd,VIDIOC_QBUF,&buf);
        if(res==-1){
            perror("ioctl QBUF");
            exit(-1);
        }
    }

    //为current分配空间
    current.start = (char *)malloc(max_len);
    if(current.start==NULL){
        perror("malloc");
        exit(-1);
    }

    //8.启动摄像头采集
    enum v4l2_buf_type buf_type= V4L2_BUF_TYPE_VIDEO_CAPTURE;
    res = ioctl(camera_fd,VIDIOC_STREAMON,&buf_type);
    if(res==-1){
        perror("ioctl STREAMON");
        exit(-1);
    }
}

//释放摄像头
void CameraThread::camera_release()
{
    //结束采集
    enum v4l2_buf_type buf_type= V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int res = ioctl(camera_fd,VIDIOC_STREAMOFF,&buf_type);
    if(res==-1){
        perror("ioctl STREAMON");
        exit(-1);
    }

    //解除映射
    for(size_t i=0;i<4;i++){
        munmap(buffer[i].start,buffer[i].length);
    }
    free(current.start);
    close(camera_fd);
}


int CameraThread::yuyv2rgb(int y, int u, int v)
{
    unsigned int pixel24 = 0;
    unsigned char *pixel = (unsigned char *)&pixel24;
    int r, g, b;
    static int  ruv, guv, buv;

    if(sign3)
    {
        sign3 = 0;
        ruv = 1159*(v-128);
        guv = 380*(u-128) + 813*(v-128);
        buv = 2018*(u-128);
    }

    r = (1164*(y-16) + ruv) / 1000;
    g = (1164*(y-16) - guv) / 1000;
    b = (1164*(y-16) + buv) / 1000;

    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;

    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;

    return pixel24;
}

int CameraThread::yuyv2rgb0(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
    unsigned int in, out;
    int y0, u, y1, v;
    unsigned int pixel24;
    unsigned char *pixel = (unsigned char *)&pixel24;
    unsigned int size = width*height*2;

    for(in = 0, out = 0; in < size; in += 4, out += 6)
    {
        y0 = yuv[in+0];
        u  = yuv[in+1];
        y1 = yuv[in+2];
        v  = yuv[in+3];

        sign3 = 1;
        pixel24 = yuyv2rgb(y0, u, v);
        rgb[out+0] = pixel[0];
        rgb[out+1] = pixel[1];
        rgb[out+2] = pixel[2];

        pixel24 = yuyv2rgb(y1, u, v);
        rgb[out+3] = pixel[0];
        rgb[out+4] = pixel[1];
        rgb[out+5] = pixel[2];

    }
    return 0;
}


//人脸识别预测
int CameraThread::Predict(Mat src_image)
{
    Mat face_test;
    int predict = 0;
    //截取的ROI人脸尺寸调整
    if (src_image.rows >= 120)
    {
       ::resize(src_image, face_test, Size(92, 112));//改变图像大小，使用双线性差值
    }
    //判断是否正确检测ROI
    if (!face_test.empty())
    {
       predict = model->predict(face_test);//测试图像应该是灰度图
    }
    return predict;
}



//摄像头采集的YUYV格式转换为JPEG格式
int CameraThread::compress_yuyv_to_jpeg(unsigned char *buf, unsigned char *buffer, int size, int quality)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    unsigned char *line_buffer, *yuyv;
    int z;
    static int written;
    //int count = 0;
    //printf("%s\n", buf);

    line_buffer = new unsigned char [1920];
    yuyv = buf;//将YUYV格式的图片数据赋给YUYV指针
//    printf("compress start...\n");

    cinfo.err = jpeg_std_error (&jerr);
    jpeg_create_compress (&cinfo);

    /* jpeg_stdio_dest (&cinfo, file); */

    dest_buffer(&cinfo, buffer, size, &written);

    cinfo.image_width = WIDTH;
    cinfo.image_height = HEIGHT;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;


    jpeg_set_defaults (&cinfo);
    jpeg_set_quality (&cinfo, quality, TRUE);
    jpeg_start_compress (&cinfo, TRUE);

    z = 0;

    while (cinfo.next_scanline < HEIGHT)
    {
        int x;
        unsigned char *ptr = line_buffer;
        for (x = 0; x < WIDTH; x++)
        {
            int r, g, b;
            int y, u, v;
            if (!z)
                y = yuyv[0] << 8;
            else
                y = yuyv[2] << 8;

            u = yuyv[1] - 128;
            v = yuyv[3] - 128;

            r = (y + (359 * v)) >> 8;
            g = (y - (88 * u) - (183 * v)) >> 8;
            b = (y + (454 * u)) >> 8;
            //r = y + v + (v * 103) >> 8;
            //g = y - (u * 88) >> 8 - (v * 183) >> 8;
            //b = y + u + (u * 198) >> 8;

            *(ptr++) = (r > 255) ? 255 : ((r < 0) ? 0 : r);
            *(ptr++) = (g > 255) ? 255 : ((g < 0) ? 0 : g);
            *(ptr++) = (b > 255) ? 255 : ((b < 0) ? 0 : b);

            if (z++)
            {
                z = 0;
                yuyv += 4;
            }

        }
        row_pointer[0] = line_buffer;
        jpeg_write_scanlines (&cinfo, row_pointer, 1);

    }

    jpeg_finish_compress (&cinfo);
    jpeg_destroy_compress (&cinfo);
    free (line_buffer);

    return (written);

}

void CameraThread::dest_buffer(j_compress_ptr cinfo, unsigned char *buffer, int size, int *written)
{
    mjpg_dest_ptr dest;
    if (cinfo->dest == NULL) {
    cinfo->dest = (struct jpeg_destination_mgr *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(mjpg_destination_mgr));
    }

    dest = (mjpg_dest_ptr)cinfo->dest;
    dest->pub.init_destination = init_destination;
    dest->pub.empty_output_buffer = empty_output_buffer;
    dest->pub.term_destination = term_destination;
    dest->outbuffer = buffer;
    dest->outbuffer_size = size;
    dest->outbuffer_cursor = buffer;
    dest->written = written;

}



