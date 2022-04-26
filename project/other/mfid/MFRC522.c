
#include "MFRC522.h"
#include <linux/delay.h>

u8  irq_regdata;
u16 wait_count;
u8  error_regdata;
u8  last_bitsdata;

/*
MFRC522_Initializtion();	
main()
{
	while(1)
	{
		MFRC522Test();
		delay_s(1);
	}	
}
*/


//MFRC522数据区

u8  mfrc552pidbuf[18];
u8  card_pydebuf[2];
u8  card_numberbuf[5];
u8  card_key0Abuf[6]={0xff,0xff,0xff,0xff,0xff,0xff};//用于验卡

//用于测试
u8  card_writebuf[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
u8  card_readbuf[18];



void delay_us(u16 count)
{
	udelay(count);

}

void Delay1_us(u16 count)
{
	delay_us(count);

}

void mfrc_read_id(unsigned char * buf)
{
	u8 status;
	u8 i =0;
	char tmp[5] = {0,1,2,3,4};//初始卡号
	// printk(KERN_INFO"status :%d\n",status);
	status=MFRC522_Request(0x52, card_pydebuf);		//寻卡
	if(status==0)									//如果读到卡
	{
		MFRC522_Anticoll(buf);	//防撞处理			
		MFRC522_SelectTag(buf);//选卡
		MFRC522_Auth(0x60, 4, card_key0Abuf, buf);//验卡	
	}
	else
	{
		for(i=0;i<5;i++)
			buf[i] = tmp[i];		
	}
}


void mfrc_read(char * buf)
{
	u8 status,card_size;
	
	status=MFRC522_Request(0x52, card_pydebuf);		//寻卡
	//printk(KERN_INFO"status :%d\n",status);
	if(status==0)									//如果读到卡
	{
		status=MFRC522_Anticoll(card_numberbuf);	//防撞处理			
		card_size=MFRC522_SelectTag(card_numberbuf);//选卡
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);//验卡		
		status=MFRC522_Read(4, buf);		//读卡	
	}

}


void mfrc_write(char * buf)
{
	u8 status,card_size;
	
	status=MFRC522_Request(0x52, card_pydebuf);		//寻卡
	if(status==0)									//如果读到卡
	{
		status=MFRC522_Anticoll(card_numberbuf);	//防撞处理			
		card_size=MFRC522_SelectTag(card_numberbuf);//选卡
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);//验卡		
		status=MFRC522_Write(4, buf);				//写卡
	}	


}


/*
void MFRC522Test(void)
{
	u8 i,j,status,card_size;
	//
	status=MFRC522_Request(0x52, card_pydebuf);			//寻卡
	printf("status : %d\n",status);
	//
	if(status==0)		//如果读到卡
	{
		status=MFRC522_Anticoll(card_numberbuf);			//防撞处理			
		card_size=MFRC522_SelectTag(card_numberbuf);	//选卡
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);	//验卡
		status=MFRC522_Write(4, card_writebuf);				//写卡（写卡要小心，特别是各区的块3）
		status=MFRC522_Read(4, card_readbuf);					//读卡
		//MFRC522_Halt();															//使卡进入休眠状态
		//卡类型显示
		printf("卡类型显示 : %x %x \n",card_pydebuf[0],card_pydebuf[1]);
	
		//卡序列号显，最后一字节为卡的校验码
		printf("卡序列 :");
		for(i=0;i<5;i++)
		{
			printf(" %d ",card_numberbuf[i]);
		}
		printf(" \n ");
		printf("卡容量 %d Kbits:  \n",card_size);

		//读一个块的数据显示
		printf("数据 : ");
		for(i=0;i<2;i++)		//分两行显示
		{
			for(j=0;j<9;j++)	//每行显示8个
			{
				printf(" %x ",card_readbuf[j+i*9]);
			}
		}
	 
	MFRC522_Reset();             
	Write_MFRC522(TxAutoReg,0x40); 		//100%ASK     
	Write_MFRC522(ModeReg,0x3D); 		//CRC初始值0x6363
	AntennaOn();

	}	
}
*/

//SPI3初始化
void STM32_SPI3_Init(void) 
{ 
	//不使能芯片
	M_CS(0);
																						//启动SP3
}

//
void SPI3_Send(u8 val)  
{ 
	u8 i = 0;
	M_SCK(0);
	for(i=0; i<8; i++)
	{
		//准备数据
		if( val & (1<<(7-i)))  
			M_MOSI(1); //引脚输出1
		else
			M_MOSI(0); //引脚输出0
		delay_us(3);
		M_SCK(1);
		delay_us(3);			
		M_SCK(0);
	}

}
//
u8 SPI3_Receive(void)  
{ 
	
	u8 i = 0;
	u8 temp = 0; 
	M_SCK(0);
	for(i=0; i<8; i++)
	{
		M_MOSI(0); //引脚输出0
		delay_us(3);
		M_SCK(1);
		delay_us(3);
		//接受数据
		if(M_MISO() == 1)
		{
			temp |= (1<<(7-i));
		}			
		M_SCK(0);
	}

  return temp; 
}
//功能描述?∠騇FRC522的某一寄存器写一个字节数据
//输入参数??addr--寄存器地址??val--要写入的值
void Write_MFRC522(u8 addr, u8 val) 
{
	//地址格式??0XXXXXX0  
	M_CS(0);   
	SPI3_Send((addr<<1)&0x7E);  
	SPI3_Send(val);    
	M_CS(1); 
}
//功能描述?〈覯FRC522的某一寄存器读一个字节数据
//输入参数??addr--寄存器地址
//返 回 值?》祷囟寥〉降囊桓鲎纸谑?据 
u8 Read_MFRC522(u8 addr) 
{  
	u8 val;
	//地址格式??1XXXXXX0   
	M_CS(0);     
	SPI3_Send(((addr<<1)&0x7E)|0x80);   
	val=SPI3_Receive();    
	M_CS(1); 
	//   
	return val;  
}
//下面两个函数只对能读写位有效
//功能描述?≈肦C522寄存器位
//输入参数??reg--寄存器地址;mask--置位值
void SetBitMask(u8 reg, u8 mask)   
{     
	u8 tmp=0;
	//     
	tmp=Read_MFRC522(reg);     
	Write_MFRC522(reg,tmp|mask);  // set bit mask 
}
//功能描述?∏錜C522寄存器位
//输入参数??reg--寄存器地址;mask--清位值
void ClearBitMask(u8 reg, u8 mask)   
{     
	u8 tmp=0;
	//     
	tmp=Read_MFRC522(reg);     
	Write_MFRC522(reg,tmp&(~mask));  //clear bit mask 
}
//功能描述?】?启天线,每次启动或关闭天线发射之间应至少有1ms的间隔
void AntennaOn(void) 
{  
	u8 temp;
	//   
	temp=Read_MFRC522(TxControlReg);  
	if ((temp&0x03)==0)  
	{   
		SetBitMask(TxControlReg,0x03);  
	}
}
//功能描述?」乇仗煜?,每次启动或关闭天线发射之间应至少有1ms的间隔
void AntennaOff(void) 
{  
	ClearBitMask(TxControlReg,0x03);
}
//功能描述?「次籑FRC522
void MFRC522_Reset(void) 
{ 
	//外复位可以不用
	M_RST(1);
	delay_us(1);
	M_RST(0);
	delay_us(1);
	M_RST(1);
	delay_us(1); 
	//内复位   
	Write_MFRC522(CommandReg, PCD_RESETPHASE); 
}
//
void MFRC522_Initializtion(void) 
{
	STM32_SPI3_Init();  
	MFRC522_Reset();         
	//Timer: TPrescaler*TreloadVal/6.78MHz = 0xD3E*0x32/6.78=25ms     
	Write_MFRC522(TModeReg,0x8D);				//TAuto=1为自动计数模式，受通信协议影向。低4位为预分频值的高4位
	//Write_MFRC522(TModeReg,0x1D);				//TAutoRestart=1为自动重载计时，0x0D3E是0.5ms的定时初值//test    
	Write_MFRC522(TPrescalerReg,0x3E); 	//预分频值的低8位     
	Write_MFRC522(TReloadRegL,0x32);		//计数器的低8位                
	Write_MFRC522(TReloadRegH,0x00);		//计数器的高8位       
	Write_MFRC522(TxAutoReg,0x40); 			//100%ASK     
	Write_MFRC522(ModeReg,0x3D); 				//CRC初始值0x6363
	Write_MFRC522(CommandReg,0x00);			//启动MFRC522  
	//Write_MFRC522(RFCfgReg, 0x7F);    //RxGain = 48dB调节卡感应距离      
	AntennaOn();          							//打开天线 
}
//功能描述??RC522和ISO14443卡通讯
//输入参数??command--MF522命令字
//					sendData--通过RC522发送到卡片的数据
//					sendLen--发送的数据长度
//					BackData--接收到的卡片返回数据
//					BackLen--返回数据的位长度
//返 回 值?⒊晒Ψ祷豈I_O
u8 MFRC522_ToCard(u8 command, u8 *sendData, u8 sendLen, u8 *backData, u16 *backLen) 
{
	u8  status=MI_ERR;
	u8  irqEn=0x00;
	u8  waitIRq=0x00;
	u8  lastBits;
	u8  n;
	u16 i;
	//根据命预设中断参数
	switch (command)     
	{         
		case PCD_AUTHENT:  		//认证卡密   
			irqEn 	= 0x12;			//    
			waitIRq = 0x10;			//    
			break;
		case PCD_TRANSCEIVE: 	//发送FIFO中数据      
			irqEn 	= 0x77;			//    
			waitIRq = 0x30;			//    
			break;      
		default:    
			break;     
	}
	//
	Write_MFRC522(ComIEnReg, irqEn|0x80);		//允许中断请求     
	ClearBitMask(ComIrqReg, 0x80);  				//清除所有中断请求位               	
	SetBitMask(FIFOLevelReg, 0x80);  				//FlushBuffer=1, FIFO初始化
	Write_MFRC522(CommandReg, PCD_IDLE); 		//使MFRC522空闲   
	//向FIFO中写入数据     
	for (i=0; i<sendLen; i++)
		Write_MFRC522(FIFODataReg, sendData[i]);
	//执行命令
	Write_MFRC522(CommandReg, command);
	//天线发送数据     
	if (command == PCD_TRANSCEIVE)					//如果是卡片通信命令，MFRC522开始向天线发送数据      
		SetBitMask(BitFramingReg, 0x80);  		//StartSend=1,transmission of data starts      
	//等待接收数据完成     
	i = 10000; //i根据时钟频率调整?〔僮鱉1卡最大等待时间25ms     
	do      
	{        
		n = Read_MFRC522(ComIrqReg);
		//irq_regdata=n;	//test         
		i--;
		//wait_count=i;		//test		     
	}while ((i!=0) && !(n&0x01) && !(n&waitIRq));	//接收完就退出n=0x64
	//停止发送
	ClearBitMask(BitFramingReg, 0x80);   		//StartSend=0
	//如果在25ms内读到卡
	if (i != 0)     
	{            
		if(!(Read_MFRC522(ErrorReg) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr         
		{            
			if (n & irqEn & 0x01)			//                  
				status = MI_NOTAGERR;		//
			//
			if (command == PCD_TRANSCEIVE)             
			{                 
				n = Read_MFRC522(FIFOLevelReg);		//n=0x02                
				lastBits = Read_MFRC522(ControlReg) & 0x07;	//lastBits=0               
				if (lastBits!=0)                         
					*backLen = (n-1)*8 + lastBits; 
				else
					*backLen = n*8;									//backLen=0x10=16
				//
				if (n == 0)                         
				 	n = 1;                        
				if (n > MAX_LEN)         
				 	n = MAX_LEN;
				//
				for (i=0; i<n; i++)                 
					backData[i] = Read_MFRC522(FIFODataReg); 
			}
			//
			status = MI_OK;		
		}
		else
			status = MI_ERR;
	}	
	//
	Write_MFRC522(ControlReg,0x80);				//timer stops     
	Write_MFRC522(CommandReg, PCD_IDLE);	//
	//
	return status;
}
//功能描述?⒀翱í《寥】ɡ嘈秃?
//输入参数??reqMode--寻卡方式
//					TagType--返回卡片类型
//					0x4400 = Mifare_UltraLight
//					0x0400 = Mifare_One(S50)
//					0x0200 = Mifare_One(S70)
//					0x0800 = Mifare_Pro(X)
//					0x4403 = Mifare_DESFire
//返 回 值?⒊晒Ψ祷豈I_OK	
u8 MFRC522_Request(u8 reqMode, u8 *TagType)
{  
	u8  status;    
	u16 backBits;   //接收到的数据位数
	//   
	Write_MFRC522(BitFramingReg, 0x07);  //TxLastBists = BitFramingReg[2..0]   
	TagType[0] = reqMode;  
	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits); 
	// 
	if ((status != MI_OK) || (backBits != 0x10))  
	{       
		status = MI_ERR;
	}
	//  
	return status; 
}
//功能描述?⒎莱逋患觳猹《寥⊙≈锌ㄆ?的卡序列号
//输入参数??serNum--返回4字节卡序列号,第5字节为校验字节
//返 回 值?⒊晒Ψ祷豈I_OK
u8 MFRC522_Anticoll(u8 *serNum) 
{     
	u8  status;     
	u8  i;     
	u8  serNumCheck=0;     
	u16 unLen;
	//           
	ClearBitMask(Status2Reg, 0x08);  			//TempSensclear     
	ClearBitMask(CollReg,0x80);   				//ValuesAfterColl  
	Write_MFRC522(BitFramingReg, 0x00);  	//TxLastBists = BitFramingReg[2..0]
	serNum[0] = PICC_ANTICOLL1;     
	serNum[1] = 0x20;     
	status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
	//      
	if (status == MI_OK)
	{   
		//校验卡序列号   
		for(i=0;i<4;i++)   
			serNumCheck^=serNum[i];
		//
		if(serNumCheck!=serNum[i])        
			status=MI_ERR;
	}
	SetBitMask(CollReg,0x80);  //ValuesAfterColl=1
	//      
	return status;
}
//功能描述?⒂肕F522计算CRC
//输入参数??pIndata--要读数CRC的数据??len--数据长度??pOutData--计算的CRC结果
void CalulateCRC(u8 *pIndata, u8 len, u8 *pOutData) 
{     
	u16 i;
	u8  n;
	//      
	ClearBitMask(DivIrqReg, 0x04);   			//CRCIrq = 0     
	SetBitMask(FIFOLevelReg, 0x80);   		//清FIFO指针     
	Write_MFRC522(CommandReg, PCD_IDLE);   
	//向FIFO中写入数据      
	for (i=0; i<len; i++)
		Write_MFRC522(FIFODataReg, *(pIndata+i));
	//开始RCR计算
	Write_MFRC522(CommandReg, PCD_CALCCRC);
	//等待CRC计算完成     
	i = 1000;     
	do      
	{         
		n = Read_MFRC522(DivIrqReg);         
		i--;     
	}while ((i!=0) && !(n&0x04));   //CRCIrq = 1
	//读取CRC计算结果     
	pOutData[0] = Read_MFRC522(CRCResultRegL);     
	pOutData[1] = Read_MFRC522(CRCResultRegH);
	Write_MFRC522(CommandReg, PCD_IDLE);
}
//功能描述?⒀】í《寥】ù娲⑵魅萘?
//输入参数??serNum--传入卡序列号
//返 回 值?⒊晒Ψ祷乜ㄈ萘?
u8 MFRC522_SelectTag(u8 *serNum) 
{     
	u8  i;     
	u8  status;     
	u8  size;     
	u16 recvBits;     
	u8  buffer[9];
	//     
	buffer[0] = PICC_ANTICOLL1;	//防撞码1     
	buffer[1] = 0x70;
	buffer[6] = 0x00;						     
	for (i=0; i<4; i++)					
	{
		buffer[i+2] = *(serNum+i);	//buffer[2]-buffer[5]为卡序列号
		buffer[6]  ^=	*(serNum+i);	//卡校验码
	}
	//
	CalulateCRC(buffer, 7, &buffer[7]);	//buffer[7]-buffer[8]为RCR校验码
	ClearBitMask(Status2Reg,0x08);
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
	//
	if ((status == MI_OK) && (recvBits == 0x18))    
		size = buffer[0];     
	else    
		size = 0;
	//	     
	return size; 
}
//功能描述?Ｑ橹たㄆ?密码
//输入参数??authMode--密码验证模式
//					0x60 = 验证A密钥
//					0x61 = 验证B密钥
//					BlockAddr--块地址
//					Sectorkey--扇区密码
//					serNum--卡片序列号??4字节
//返 回 值?３晒Ψ祷豈I_OK
u8 MFRC522_Auth(u8 authMode, u8 BlockAddr, u8 *Sectorkey, u8 *serNum) 
{     
	u8  status;     
	u16 recvBits;     
	u8  i;  
	u8  buff[12];    
	//验证模式+块地址+扇区密码+卡序列号     
	buff[0] = authMode;		//验证模式     
	buff[1] = BlockAddr;	//块地址     
	for (i=0; i<6; i++)
		buff[i+2] = *(Sectorkey+i);	//扇区密码
	//
	for (i=0; i<4; i++)
		buff[i+8] = *(serNum+i);		//卡序列号
	//
	status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
	//      
	if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
		status = MI_ERR;
	//
	return status;
}
//功能描述?６量槭?据
//输入参数??blockAddr--块地址;recvData--读出的块数据
//返 回 值?〕晒Ψ祷豈I_OK
u8 MFRC522_Read(u8 blockAddr, u8 *recvData) 
{     
	u8  status;     
	u16 unLen;
	//      
	recvData[0] = PICC_READ;     
	recvData[1] = blockAddr;     
	CalulateCRC(recvData,2, &recvData[2]);     
	status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);
	//
	if ((status != MI_OK) || (unLen != 0x90))
		status = MI_ERR;
	//
	return status;
}
//功能描述?⌒纯槭?据
//输入参数??blockAddr--块地址;writeData--向块写16字节数据
//返 回 值?〕晒Ψ祷豈I_OK
u8 MFRC522_Write(u8 blockAddr, u8 *writeData) 
{     
	u8  status;     
	u16 recvBits;     
	u8  i;  
	u8  buff[18];
	//           
	buff[0] = PICC_WRITE;     
	buff[1] = blockAddr;     
	CalulateCRC(buff, 2, &buff[2]);     
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);
	//
	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
		status = MI_ERR;
	//
	if (status == MI_OK)     
	{         
		for (i=0; i<16; i++)  //向FIFO写16Byte数据                     
			buff[i] = *(writeData+i);
		//                     
		CalulateCRC(buff, 16, &buff[16]);         
		status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);           
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))               
			status = MI_ERR;         
	}          
	return status;
}
//功能描述?∶?令卡片进入休眠状态
void MFRC522_Halt(void) 
{    
	u16 unLen;     
	u8  buff[4];
	//       
	buff[0] = PICC_HALT;     
	buff[1] = 0;     
	CalulateCRC(buff, 2, &buff[2]);       
	MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}
//
