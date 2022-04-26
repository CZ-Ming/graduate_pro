#include "as608.h"
#include <string.h>
#include <stdio.h>

//串口和指纹模块相关的 类的具体实现


usart3::usart3()
{

}


/* 设置串口参数:9600速率 */
int usart3::serial_init(const char * path,speed_t speed)//B9600
{
    //声明设置串口的结构体
    struct termios termios_new;

    /*O_NOCTTY：表示告诉linux系统这个程序不会成为这个端口的控制终端，否则，所有的输入
      比如键盘上过来的Ctrl+C中止信号，会影响你的进程
    O_NONBLOCK:使I/O变成非阻塞模式(non-blocking)，
    在读取不到数据或是写入缓冲区已满会马上return，而不会阻塞等待。
    */
    this->g_usart_fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (this->g_usart_fd < 0)
    {
        fprintf(stderr, "Open %s fail!\n" , path);
        return -1;
    }


    //先清空该结构体
    bzero( &termios_new, sizeof(termios_new));
    //	cfmakeraw()设置终端属性，就是设置termios结构中的各个参数。
    cfmakeraw(&termios_new);
    //设置波特率
    //termios_new.c_cflag=(B9600);
    cfsetispeed(&termios_new, speed);
    cfsetospeed(&termios_new, speed);
    //CLOCAL和CREAD分别用于本地连接和接收使能，因此，首先要通过位掩码的方式激活这两个选项。
    termios_new.c_cflag |= CLOCAL | CREAD;
    //通过掩码设置数据位为8位
    termios_new.c_cflag &= ~CSIZE;
    termios_new.c_cflag |= CS8;
    //设置无奇偶校验
    termios_new.c_cflag &= ~PARENB;
    //一位停止位
    termios_new.c_cflag &= ~CSTOPB;
    tcflush(this->g_usart_fd,TCIFLUSH);
    // 可设置接收字符和等待时间，无特殊要求可以将其设置为0
    termios_new.c_cc[VTIME] = 10;//等待时间，单位百毫秒 （读）
    termios_new.c_cc[VMIN] = 1;// 最小字节数 （读）
    //清空串口输入/输出缓冲区
    tcflush (this->g_usart_fd, TCIOFLUSH);
    //完成配置后，可以使用以下函数激活串口设置
    if(tcsetattr(this->g_usart_fd,TCSANOW,&termios_new) )
        printf("Setting the serial failed!\n");
    return 0;

}

int usart3::serial_rx(unsigned char * rbuf,unsigned int len,struct timeval timeout)
{

    fd_set rdfd;
    int  ret= -1;
    unsigned char *p = rbuf;

    FD_ZERO(&rdfd);
    FD_SET(this->g_usart_fd,&rdfd);

    ret = select(this->g_usart_fd + 1,&rdfd, NULL,NULL,&timeout);

    switch(ret)
    {
        case -1:
            perror("select error\n");
            break;
        case  0:
            //printf("Request timed out.\n");
            break;
        default:
            ret = read(this->g_usart_fd, p, len);
            break;
    }
    return ret;
}

int usart3::serial_tx(unsigned char* wbuf,unsigned int len)
{
    return write(this->g_usart_fd, wbuf, len);
}

int usart3::serial_close(void)
{
    return close(this->g_usart_fd);
}





as608::as608()
{

}


u32 AS608Addr = 0XFFFFFFFF; //默认


//串口发送一个字节
 void as608::MYUSART_SendData(unsigned char data)
{
    unsigned char txd = data;
    serial_tx(&txd,1);
}

//发送包头
 void as608::SendHead(void)
{
    MYUSART_SendData(0xEF);
    MYUSART_SendData(0x01);
}

//发送地址
 void as608::SendAddr(void)
{
    MYUSART_SendData(AS608Addr >> 24);
    MYUSART_SendData(AS608Addr >> 16);
    MYUSART_SendData(AS608Addr >> 8);
    MYUSART_SendData(AS608Addr);
}
//发送包标识,
 void as608::SendFlag(u8 flag)
{
    MYUSART_SendData(flag);
}

//发送包长度
 void as608::SendLength(int length)
{
    MYUSART_SendData(length >> 8);
    MYUSART_SendData(length);
}

//发送指令码
 void as608::Sendcmd(u8 cmd)
{
    MYUSART_SendData(cmd);
}

//发送校验和
 void as608::SendCheck(u16 check)
{
    MYUSART_SendData(check >> 8);
    MYUSART_SendData(check);
}

//判断中断接收的数组有没有应答包
//waittime为等待中断接收数据的时间（单位1ms）
//返回值：数据包首地址
 u8 *as608::JudgeStr(u16 waittime)
{

    //char *data;
    u8 str[8];

    static unsigned char buf[64] = {0};
    int len;
    struct timeval timeout;

    str[0]=0xef;
    str[1]=0x01;
    str[2]=AS608Addr>>24;
    str[3]=AS608Addr>>16;
    str[4]=AS608Addr>>8;
    str[5]=AS608Addr;
    str[6]=0x07;
    str[7]='\0';

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    len = serial_rx(buf,sizeof(buf),timeout);

    if(len>0)
    {
        const char *data = strstr((const char*)buf, (const char*)str);
        if(data)
            return (u8*)data;
    }

    return NULL;
}

//录入图像 PS_GetImage
//功能:探测手指，探测到后录入指纹图像存于ImageBuffer。
//模块返回确认字
u8 as608::PS_GetImage(void)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x01);

    temp =  0x01 + 0x03 + 0x01;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//生成特征 PS_GenChar
//功能:将ImageBuffer中的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
//参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//模块返回确认字
u8 as608::PS_GenChar(u8 BufferID)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x04);
    Sendcmd(0x02);

    MYUSART_SendData(BufferID);

    temp = 0x01 + 0x04 + 0x02 + BufferID;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure=data[9];
    }
    else
    {
        ensure=0xff;
    }

    return ensure;
}

//精确比对两枚指纹特征 PS_Match
//功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
//模块返回确认字
u8 as608::PS_Match(void)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x03);

    temp = 0x01 + 0x03 + 0x03;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//搜索指纹 PS_Search
//功能:以CharBuffer1或CharBuffer2中的特征文件搜索整个或部分指纹库.若搜索到，则返回页码。
//参数:  BufferID @ref CharBuffer1	CharBuffer2
//说明:  模块返回确认字，页码（相配指纹模板）
u8 as608::PS_Search(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x08);
    Sendcmd(0x04);

    MYUSART_SendData(BufferID);
    MYUSART_SendData(StartPage>>8);
    MYUSART_SendData(StartPage);
    MYUSART_SendData(PageNum>>8);
    MYUSART_SendData(PageNum);

    temp = 0x01 + 0x08 + 0x04 + BufferID + (StartPage>>8) + (u8)StartPage + (PageNum>>8) + (u8)PageNum;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
        p->pageID   =(data[10]<<8)+data[11];
        p->mathscore=(data[12]<<8)+data[13];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//合并特征（生成模板）PS_RegModel
//功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
//说明:  模块返回确认字
u8 as608::PS_RegModel(void)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x05);

    temp = 0x01 + 0x03 + 0x05;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//储存模板 PS_StoreChar
//功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
//参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID（指纹库位置号）
//说明:  模块返回确认字
u8 as608::PS_StoreChar(u8 BufferID,u16 PageID)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x06);
    Sendcmd(0x06);

    MYUSART_SendData(BufferID);
    MYUSART_SendData(PageID>>8);
    MYUSART_SendData(PageID);

    temp = 0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (u8)PageID;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//删除模板 PS_DeletChar
//功能:  删除flash数据库中指定ID号开始的N个指纹模板
//参数:  PageID(指纹库模板号)，N删除的模板个数。
//说明:  模块返回确认字
u8 as608::PS_DeletChar(u16 PageID,u16 N)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x07);
    Sendcmd(0x0C);

    MYUSART_SendData(PageID >> 8);
    MYUSART_SendData(PageID);
    MYUSART_SendData(N >> 8);
    MYUSART_SendData(N);

    temp = 0x01 + 0x07 + 0x0C + (PageID >> 8) + (u8)PageID + (N >> 8) + (u8)N;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//清空指纹库 PS_Empty
//功能:  删除flash数据库中所有指纹模板
//参数:  无
//说明:  模块返回确认字
u8 as608::PS_Empty(void)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x0D);

    temp = 0x01 + 0x03 + 0x0D;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure=data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//写系统寄存器 PS_WriteReg
//功能:  写模块寄存器
//参数:  寄存器序号RegNum:4\5\6
//说明:  模块返回确认字
u8 as608::PS_WriteReg(u8 RegNum,u8 DATA)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x05);
    Sendcmd(0x0E);

    MYUSART_SendData(RegNum);
    MYUSART_SendData(DATA);

    temp = RegNum+DATA + 0x01 + 0x05 + 0x0E;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    if(ensure == 0)
    {
        printf("\r\n设置参数成功！");
    }
    else
    {
        printf("\r\n%s",EnsureMessage(ensure));
    }

    return ensure;
}

//读系统基本参数 PS_ReadSysPara
//功能:  读取模块的基本参数（波特率，包大小等)
//参数:  无
//说明:  模块返回确认字 + 基本参数（16bytes）
u8 as608::PS_ReadSysPara(SysPara *p)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x0F);

    temp = 0x01 + 0x03 + 0x0F;
    SendCheck(temp);

    data = JudgeStr(1000);
    if(data)
    {
        ensure = data[9];
        p->PS_max = (data[14]<<8) + data[15];
        p->PS_level = data[17];
        p->PS_addr=(data[18]<<24) + (data[19]<<16)+(data[20]<<8) + data[21];
        p->PS_size = data[23];
        p->PS_N = data[25];
    }
    else
    {
        ensure = 0xff;
    }

    if(ensure == 0x00)
    {
        //printf("\r\n模块最大指纹容量=%d",p->PS_max);
        // printf("\r\n对比等级=%d",p->PS_level);
        // printf("\r\n地址=%x",p->PS_addr);
        // printf("\r\n波特率=%d",p->PS_N*9600);
    }
    else
    {
        //printf("\r\n%s",EnsureMessage(ensure));
    }
   // printf("\n");

    return ensure;
}

//设置模块地址 PS_SetAddr
//功能:  设置模块地址
//参数:  PS_addr
//说明:  模块返回确认字
u8 as608::PS_SetAddr(u32 PS_addr)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x07);
    Sendcmd(0x15);

    MYUSART_SendData(PS_addr>>24);
    MYUSART_SendData(PS_addr>>16);
    MYUSART_SendData(PS_addr>>8);
    MYUSART_SendData(PS_addr);

    temp = 0x01 + 0x07 + 0x15 + (u8)(PS_addr>>24) + (u8)(PS_addr>>16) + (u8)(PS_addr>>8) + (u8)PS_addr;
    SendCheck(temp);
    AS608Addr = PS_addr;//发送完指令，更换地址

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
    }
    else
    {
        ensure = 0xff;
    }

    AS608Addr = PS_addr;

    if(ensure==0x00)
    {
        printf("\r\n设置地址成功！");
    }
    else
    {
        printf("\r\n%s",EnsureMessage(ensure));
    }

    return ensure;
}

//读有效模板个数 PS_ValidTempleteNum
//功能：读有效模板个数
//参数: 无
//说明: 模块返回确认字+有效模板个数ValidN
u8 as608::PS_ValidTempleteNum(u16 *ValidN)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x03);
    Sendcmd(0x1d);

    temp = 0x01+0x03+0x1d;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure = data[9];
        *ValidN = (data[10]<<8) + data[11];
    }
    else
    {
        ensure = 0xff;
    }

    if(ensure == 0x00)
    {
        //printf("\r\n有效指纹个数=%d",(data[10]<<8)+data[11]);
    }
    else
    {
        //printf("\r\n%s",EnsureMessage(ensure));
    }

    return ensure;
}

//功能： 模块内部为用户开辟了256bytes的FLASH空间用于存用户记事本,
//	该记事本逻辑上被分成 16 个页。
//参数:  NotePageNum(0~15),Byte32(要写入内容，32个字节)
//说明:  模块返回确认字
u8 as608::PS_WriteNotepad(u8 NotePageNum,u8 *Byte32)
{
    u16 temp;
    u8  ensure, i;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(36);
    Sendcmd(0x18);
    MYUSART_SendData(NotePageNum);

    for(i = 0; i < 32; i++)
    {
        MYUSART_SendData(Byte32[i]);
        temp += Byte32[i];
    }
    temp = 0x01 + 36 + 0x18 + NotePageNum + temp;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure=data[9];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//读记事本PS_ReadNotepad
//功能：  读取FLASH用户区的128bytes数据
//参数:  NotePageNum(0~15)
//说明:  模块返回确认字+用户信息
u8 as608::PS_ReadNotepad(u8 NotePageNum,u8 *Byte32)
{
    u16 temp;
    u8  ensure, i;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x04);
    Sendcmd(0x19);

    MYUSART_SendData(NotePageNum);

    temp = 0x01 + 0x04 + 0x19 + NotePageNum;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure=data[9];
        for(i = 0; i < 32; i++)
        {
            Byte32[i] = data[10+i];
        }
    }
    else
    {
        ensure = 0xff;
    }
    return ensure;
}

//高速搜索PS_HighSpeedSearch
//功能：以 CharBuffer1或CharBuffer2中的特征文件高速搜索整个或部分指纹库。
//		  若搜索到，则返回页码,该指令对于的确存在于指纹库中 ，且登录时质量
//		  很好的指纹，会很快给出搜索结果。
//参数:  BufferID， StartPage(起始页)，PageNum（页数）
//说明:  模块返回确认字+页码（相配指纹模板）
u8 as608::PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p)
{
    u16 temp;
    u8  ensure;
    u8  *data;

    SendHead();
    SendAddr();
    SendFlag(0x01);//命令包标识
    SendLength(0x08);
    Sendcmd(0x1b);

    MYUSART_SendData(BufferID);
    MYUSART_SendData(StartPage>>8);
    MYUSART_SendData(StartPage);
    MYUSART_SendData(PageNum>>8);
    MYUSART_SendData(PageNum);

    temp = 0x01 + 0x08 + 0x1b + BufferID + (StartPage>>8) + (u8)StartPage + (PageNum>>8) + (u8)PageNum;
    SendCheck(temp);

    data = JudgeStr(2000);
    if(data)
    {
        ensure=data[9];
        p->pageID 	 = (data[10]<<8) +data[11];
        p->mathscore = (data[12]<<8) +data[13];
    }
    else
    {
        ensure = 0xff;
    }

    return ensure;
}

//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（正确地址）
u8 as608::PS_HandShake(u32 *PS_Addr)
{
    unsigned char buf[64];
    struct timeval timeout;

    SendHead();
    SendAddr();

    MYUSART_SendData(0X01);
    MYUSART_SendData(0X00);
    MYUSART_SendData(0X00);

    //超时两秒
    timeout.tv_sec =2;
    timeout.tv_usec =0;

    int rt = serial_rx(buf,sizeof(buf),timeout);

    if(rt>0)//接收到数据
    {
        //判断是不是模块返回的应答包
        if(buf[0] == 0XEF && buf[1] == 0X01 && buf[6]==0X07)
        {
            *PS_Addr = (buf[2]<<24) + (buf[3]<<16)+(buf[4]<<8) + (buf[5]);
            return 0;
        }
    }
    return 1;
}

//模块应答包确认码信息解析
//功能：解析确认码错误信息返回信息
//参数: ensure
const char *as608::EnsureMessage(u8 ensure)
{
    const char *p;
    switch(ensure)
    {
        case  0x00:
            p = "OK";break;
        case  0x01:
            p = "数据包接收错误";break;
        case  0x02:
            p = "传感器上没有手指";break;
        case  0x03:
            p = "录入指纹图像失败";break;
        case  0x04:
            p = "指纹图像太干、太淡而生不成特征";break;
        case  0x05:
            p = "指纹图像太湿、太糊而生不成特征";break;
        case  0x06:
            p = "指纹图像太乱而生不成特征";break;
        case  0x07:
            p = "指纹图像正常，但特征点太少（或面积太小）而生不成特征";break;
        case  0x08:
            p = "指纹不匹配";break;
        case  0x09:
            p = "没搜索到指纹";break;
        case  0x0a:
            p = "特征合并失败";break;
        case  0x0b:
            p = "访问指纹库时地址序号超出指纹库范围";
        case  0x10:
            p = "删除模板失败";break;
        case  0x11:
            p = "清空指纹库失败";break;
        case  0x15:
            p = "缓冲区内没有有效原始图而生不成图像";break;
        case  0x18:
            p = "读写 FLASH 出错";break;
        case  0x19:
            p = "未定义错误";break;
        case  0x1a:
            p = "无效寄存器号";break;
        case  0x1b:
            p = "寄存器设定内容错误";break;
        case  0x1c:
            p = "记事本页码指定错误";break;
        case  0x1f:
            p = "指纹库满";break;
        case  0x20:
            p = "地址错误";break;
        default :
            p = "模块返回确认码有误";break;
    }

    return p;
}




