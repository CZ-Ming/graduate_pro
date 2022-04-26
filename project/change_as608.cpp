#include "change_as608.h"
#include "ui_change_as608.h"

change_as608::change_as608(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_as608)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//close 的时候释放内存

    QPixmap pixmap("../ui/back.png");//打开显示的图片
    pixmap.scaled(ui->back->size(), Qt::KeepAspectRatio);//图片大小自适应标签
    ui->back->setScaledContents(true);
    ui->back->setPixmap(pixmap);//标签显示图片

    ui->addexit->setStyleSheet("border-image:url(../ui/clo.png)");
    ui->n1->setStyleSheet("border-image:url(../ui/1.png)");
    ui->n2->setStyleSheet("border-image:url(../ui/2.png)");
    ui->n3->setStyleSheet("border-image:url(../ui/3.png)");
    ui->n4->setStyleSheet("border-image:url(../ui/4.png)");
    ui->n5->setStyleSheet("border-image:url(../ui/5.png)");
    ui->n6->setStyleSheet("border-image:url(../ui/6.png)");
    ui->n7->setStyleSheet("border-image:url(../ui/7.png)");
    ui->n8->setStyleSheet("border-image:url(../ui/8.png)");
    ui->n9->setStyleSheet("border-image:url(../ui/9.png)");
    ui->n0->setStyleSheet("border-image:url(../ui/0.png)");
    ui->nok->setStyleSheet("border-image:url(../ui/ok.png)");
    ui->ncl->setStyleSheet("border-image:url(../ui/cl.png)");
    ui->label->setStyleSheet("color:rgb(255,255,255)");
    ui->label_2->setStyleSheet("color:rgb(255,255,255)");

    uart_flag = false;//串口初始化标志位，为false表示未初始化
    processnum=0;//指纹录制状态标志位
    degree =0;//超过10次没有按手指则退出

    pwd_flag = false;
    pwd =0;
    pwd_id =0;

    connect(&stimer,&QTimer::timeout,this,&change_as608::srun);//定时器用于初始化指纹模块
    connect(&mtimer,&QTimer::timeout,this,&change_as608::run);//定时器用于指纹录制
    connect(&dtimer,&QTimer::timeout,this,&change_as608::drun);//定时器用于删除指纹
    connect(&ftimer,&QTimer::timeout,this,&change_as608::frun);//定时器用于指纹验证
    stimer.start(300);//启动初始化指纹模块定时器

}

//初始化指纹模块
void change_as608::srun()
{
    if(!uart_flag)
    {
        int ret = add_as1.serial_init(DEV_PATH,B57600);//串口初始化
        if(ret<0)
        {
            ui->msgtext->append("串口初始化失败");
            return ;
        }
        uart_flag = true;
    }
    if(add_as1.PS_HandShake(&AS608Addr))//与AS608模块握手
        return ;//没有连接上则退出本次定时器

    u8 ensure = add_as1.PS_ValidTempleteNum(&ValidN);//读库指纹信息
    if(ensure != 0x00)
        ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码

    ensure = add_as1.PS_ReadSysPara(&AS608Para);//读参数
    if(ensure == 0x00)
    {
        char str[32] = {0};
        sprintf(str,"模块最大指纹为:%d",AS608Para.PS_max);
        ui->msgtext->append(str);
        sprintf(str,"库容量：%d     对比等级: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
        ui->msgtext->append(str);
    }
    else
        ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码

    stimer.stop();// 停止初始化指纹定时器
}

//录指纹按
void change_as608::on_addfp_clicked()
{

    ui->msgtext->clear();//清空消息
    ui->msgtext->append("指纹录制功能开启");
    degree =0;
    processnum=0;
    pwd_flag = false;
    on_ncl_clicked();
    mtimer.start(1000);//开启定时器
}

//输入指纹ID号按钮
void change_as608::on_nok_clicked()
{
    if(pwd>=0 && pwd <= 300)
    {
         pwd_flag = true;
         pwd_id = pwd;
    }
    else
    {
        ui->msgtext->append("输入ID号不在指定范围内");
        ui->msgtext->append("请输入储存ID(0~299):");
    }
    on_ncl_clicked();

}
//指纹录制定时器
void change_as608::run()
{
    u8 ensure;
    switch (processnum)
    {
        case 0:
        {
            degree++;
            ui->msgtext->append("请按指纹...");

            ensure=add_as1.PS_GetImage();
            if(ensure==0x00)
            {
                ensure=add_as1.PS_GenChar(CharBuffer1);//生成特征
                if(ensure==0x00)
                {
                    ui->msgtext->append("指纹正常");
                    degree=0;
                    processnum=1;//跳到下一步
                }
                else
                    ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
            }
            else
                ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
        }break;

        case 1:
        {

            degree++;
            ui->msgtext->append("请按再按一次指纹..");

            ensure=add_as1.PS_GetImage();
            if(ensure==0x00)
            {
                ensure=add_as1.PS_GenChar(CharBuffer2);//生成特征
                if(ensure==0x00)
                {
                    ui->msgtext->append("指纹正常");
                    degree=0;
                    processnum=2;//跳到下一步
                }
                else
                    ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
            }
            else
                ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
        }break;

        case 2:
        {
            ui->msgtext->append("对比两次指纹...");

            ensure=add_as1.PS_Match();
            if(ensure==0x00)
            {
                ui->msgtext->append("对比成功,两次指纹一致");
                processnum=3;//跳到下一步
            }
            else
            {
                ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
                degree=0;
                processnum=0;//跳回开始
            }
        }break;

        case 3:
        {

            ui->msgtext->append("生成指纹模板...");

            ensure=add_as1.PS_RegModel();
            if(ensure==0x00)
            {
                ui->msgtext->append("生成指纹模板成功...");
                ui->msgtext->append("请输入储存ID(0~299):");
                processnum=4;//跳到下一步
            }
            else
            {
                degree=0;
                processnum=0;//跳回开始
                ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
            }
        }break;

        case 4:
        {
            if(pwd_flag)
            {
                pwd_flag = false;
                u16 ID = pwd_id;

                char str[32] = {0};
                sprintf(str,"输入ID号为 ：%d",ID);
                ui->msgtext->append(str);

                ensure=add_as1.PS_StoreChar(CharBuffer2,ID);//储存模板
                if(ensure==0x00)
                {
                    ui->msgtext->append("录入指纹成功");
                    add_as1.PS_ValidTempleteNum(&ValidN);//读库指纹容量
                    sprintf(str,"剩余指纹容量 : %d", AS608Para.PS_max-ValidN);//显示剩余指纹容量
                    ui->msgtext->append(str);
                    ui->msgtext->append("录制结束");
                    mtimer.stop();
                }
                else
                {
                    degree=0;
                    processnum=0;//跳回开始
                    ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
                }
            }

        }break;
    }

    if(degree==10)//超过10次没有按手指则退出
    {
        ui->msgtext->append(" 录制结束");
        mtimer.stop();
    }
}

//删除指纹按钮
void change_as608::on_delfp_clicked()
{
    ui->msgtext->clear();//清空消息
    ui->msgtext->append("指纹删除");
    ui->msgtext->append("请输入需要删除的指纹的ID");
    pwd_flag = false;
    dtimer.start(1000);//开启定时器
}

//删除指纹
void change_as608::drun()
{
    if(pwd_flag)
    {
        u16 ID = pwd_id;
        u8  ensure;
        char str[32]= {0};

        pwd_flag = false;
        sprintf(str,"删除指纹ID号为:%d", ID);
        ui->msgtext->append(str);

        if(ID ==0xff00)
            ensure=add_as1.PS_Empty();
        else
            ensure=add_as1.PS_DeletChar(ID,1);//删除单个指纹
        if(ensure==0)
            ui->msgtext->append("删除指纹成功");
        else
            ui->msgtext->append(add_as1.EnsureMessage(ensure));

        add_as1.PS_ValidTempleteNum(&ValidN);//读库指纹容量
        sprintf(str,"库指纹个为: %d",AS608Para.PS_max-ValidN);
        ui->msgtext->append(str);
        sprintf(str,"有效指纹是: %d",ValidN);
        ui->msgtext->append(str);
        dtimer.stop();
    }
}

// 验证指纹按钮
void change_as608::on_findfp_clicked()
{
    ui->msgtext->clear();
    ui->msgtext->append("指纹查寻功能开启");
    degree =5;
    ftimer.start(1000);//开启定时器
}

//验证指纹
void change_as608::frun()
{
    degree--;
    u8 ensure=add_as1.PS_GetImage();
    if(ensure==0x00)//获取图像成功
    {
        ensure=add_as1.PS_GenChar(CharBuffer1);
        if(ensure==0x00) //生成特征成功
        {
            SearchResult seach;
            ensure=add_as1.PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
            if(ensure==0x00)//搜索成功
            {
                char str[32] = {0};
                ui->msgtext->append("查指纹成功");
                sprintf(str,"找到此人,ID:%d  匹配得分:%d",seach.pageID,seach.mathscore);
                ui->msgtext->append(str);
                ftimer.stop();
                return;
            }
            else
                ui->msgtext->append("查无此人");
        }
        else
            ui->msgtext->append(add_as1.EnsureMessage(ensure));//显示错误码
    }
    else
        ui->msgtext->append("请放入手指");

    if(degree <=0)
    {
        ui->msgtext->append("查寻结束");
        ftimer.stop();
    }
}





//退出
void change_as608::on_addexit_clicked()
{
    mtimer.stop();//关闭指纹录制定时
    ftimer.stop();//关闭指纹验证定时
    dtimer.stop();//关闭指纹删除定时
    stimer.stop();//关闭指纹初始化
    add_as1.serial_close();//关闭文件描述
    emit sendsignal();
    this->close();
}



change_as608::~change_as608()
{
    delete ui;
}

void change_as608::on_ncl_clicked()
{
    pwd=0;
    ui->lcdNumber->display("0");//清空lcd数字显示屏幕
}
//数字键盘
void change_as608::on_n0_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+0;
         ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n1_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+1;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n2_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+2;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n3_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+3;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n4_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+4;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n5_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+5;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n6_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+6;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n7_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+7;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n8_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+8;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}

void change_as608::on_n9_clicked()
{
    if(pwd<100000)
    {
        pwd = pwd*10+9;
        ui->lcdNumber->display(QString("%1").arg(pwd));
    }
}





