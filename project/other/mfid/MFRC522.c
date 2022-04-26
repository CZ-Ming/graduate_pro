
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


//MFRC522������

u8  mfrc552pidbuf[18];
u8  card_pydebuf[2];
u8  card_numberbuf[5];
u8  card_key0Abuf[6]={0xff,0xff,0xff,0xff,0xff,0xff};//�����鿨

//���ڲ���
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
	char tmp[5] = {0,1,2,3,4};//��ʼ����
	// printk(KERN_INFO"status :%d\n",status);
	status=MFRC522_Request(0x52, card_pydebuf);		//Ѱ��
	if(status==0)									//���������
	{
		MFRC522_Anticoll(buf);	//��ײ����			
		MFRC522_SelectTag(buf);//ѡ��
		MFRC522_Auth(0x60, 4, card_key0Abuf, buf);//�鿨	
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
	
	status=MFRC522_Request(0x52, card_pydebuf);		//Ѱ��
	//printk(KERN_INFO"status :%d\n",status);
	if(status==0)									//���������
	{
		status=MFRC522_Anticoll(card_numberbuf);	//��ײ����			
		card_size=MFRC522_SelectTag(card_numberbuf);//ѡ��
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);//�鿨		
		status=MFRC522_Read(4, buf);		//����	
	}

}


void mfrc_write(char * buf)
{
	u8 status,card_size;
	
	status=MFRC522_Request(0x52, card_pydebuf);		//Ѱ��
	if(status==0)									//���������
	{
		status=MFRC522_Anticoll(card_numberbuf);	//��ײ����			
		card_size=MFRC522_SelectTag(card_numberbuf);//ѡ��
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);//�鿨		
		status=MFRC522_Write(4, buf);				//д��
	}	


}


/*
void MFRC522Test(void)
{
	u8 i,j,status,card_size;
	//
	status=MFRC522_Request(0x52, card_pydebuf);			//Ѱ��
	printf("status : %d\n",status);
	//
	if(status==0)		//���������
	{
		status=MFRC522_Anticoll(card_numberbuf);			//��ײ����			
		card_size=MFRC522_SelectTag(card_numberbuf);	//ѡ��
		status=MFRC522_Auth(0x60, 4, card_key0Abuf, card_numberbuf);	//�鿨
		status=MFRC522_Write(4, card_writebuf);				//д����д��ҪС�ģ��ر��Ǹ����Ŀ�3��
		status=MFRC522_Read(4, card_readbuf);					//����
		//MFRC522_Halt();															//ʹ����������״̬
		//��������ʾ
		printf("��������ʾ : %x %x \n",card_pydebuf[0],card_pydebuf[1]);
	
		//�����к��ԣ����һ�ֽ�Ϊ����У����
		printf("������ :");
		for(i=0;i<5;i++)
		{
			printf(" %d ",card_numberbuf[i]);
		}
		printf(" \n ");
		printf("������ %d Kbits:  \n",card_size);

		//��һ�����������ʾ
		printf("���� : ");
		for(i=0;i<2;i++)		//��������ʾ
		{
			for(j=0;j<9;j++)	//ÿ����ʾ8��
			{
				printf(" %x ",card_readbuf[j+i*9]);
			}
		}
	 
	MFRC522_Reset();             
	Write_MFRC522(TxAutoReg,0x40); 		//100%ASK     
	Write_MFRC522(ModeReg,0x3D); 		//CRC��ʼֵ0x6363
	AntennaOn();

	}	
}
*/

//SPI3��ʼ��
void STM32_SPI3_Init(void) 
{ 
	//��ʹ��оƬ
	M_CS(0);
																						//����SP3
}

//
void SPI3_Send(u8 val)  
{ 
	u8 i = 0;
	M_SCK(0);
	for(i=0; i<8; i++)
	{
		//׼������
		if( val & (1<<(7-i)))  
			M_MOSI(1); //�������1
		else
			M_MOSI(0); //�������0
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
		M_MOSI(0); //�������0
		delay_us(3);
		M_SCK(1);
		delay_us(3);
		//��������
		if(M_MISO() == 1)
		{
			temp |= (1<<(7-i));
		}			
		M_SCK(0);
	}

  return temp; 
}
//��������?���MFRC522��ĳһ�Ĵ���дһ���ֽ�����
//�������??addr--�Ĵ�����ַ??val--Ҫд���ֵ
void Write_MFRC522(u8 addr, u8 val) 
{
	//��ַ��ʽ??0XXXXXX0  
	M_CS(0);   
	SPI3_Send((addr<<1)&0x7E);  
	SPI3_Send(val);    
	M_CS(1); 
}
//��������?���MFRC522��ĳһ�Ĵ�����һ���ֽ�����
//�������??addr--�Ĵ�����ַ
//�� �� ֵ?����ض�ȡ����һ���ֽ��?�� 
u8 Read_MFRC522(u8 addr) 
{  
	u8 val;
	//��ַ��ʽ??1XXXXXX0   
	M_CS(0);     
	SPI3_Send(((addr<<1)&0x7E)|0x80);   
	val=SPI3_Receive();    
	M_CS(1); 
	//   
	return val;  
}
//������������ֻ���ܶ�дλ��Ч
//��������?���RC522�Ĵ���λ
//�������??reg--�Ĵ�����ַ;mask--��λֵ
void SetBitMask(u8 reg, u8 mask)   
{     
	u8 tmp=0;
	//     
	tmp=Read_MFRC522(reg);     
	Write_MFRC522(reg,tmp|mask);  // set bit mask 
}
//��������?���RC522�Ĵ���λ
//�������??reg--�Ĵ�����ַ;mask--��λֵ
void ClearBitMask(u8 reg, u8 mask)   
{     
	u8 tmp=0;
	//     
	tmp=Read_MFRC522(reg);     
	Write_MFRC522(reg,tmp&(~mask));  //clear bit mask 
}
//��������?��?������,ÿ��������ر����߷���֮��Ӧ������1ms�ļ��
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
//��������?��ر����?,ÿ��������ر����߷���֮��Ӧ������1ms�ļ��
void AntennaOff(void) 
{  
	ClearBitMask(TxControlReg,0x03);
}
//��������?���λMFRC522
void MFRC522_Reset(void) 
{ 
	//�⸴λ���Բ���
	M_RST(1);
	delay_us(1);
	M_RST(0);
	delay_us(1);
	M_RST(1);
	delay_us(1); 
	//�ڸ�λ   
	Write_MFRC522(CommandReg, PCD_RESETPHASE); 
}
//
void MFRC522_Initializtion(void) 
{
	STM32_SPI3_Init();  
	MFRC522_Reset();         
	//Timer: TPrescaler*TreloadVal/6.78MHz = 0xD3E*0x32/6.78=25ms     
	Write_MFRC522(TModeReg,0x8D);				//TAuto=1Ϊ�Զ�����ģʽ����ͨ��Э��Ӱ�򡣵�4λΪԤ��Ƶֵ�ĸ�4λ
	//Write_MFRC522(TModeReg,0x1D);				//TAutoRestart=1Ϊ�Զ����ؼ�ʱ��0x0D3E��0.5ms�Ķ�ʱ��ֵ//test    
	Write_MFRC522(TPrescalerReg,0x3E); 	//Ԥ��Ƶֵ�ĵ�8λ     
	Write_MFRC522(TReloadRegL,0x32);		//�������ĵ�8λ                
	Write_MFRC522(TReloadRegH,0x00);		//�������ĸ�8λ       
	Write_MFRC522(TxAutoReg,0x40); 			//100%ASK     
	Write_MFRC522(ModeReg,0x3D); 				//CRC��ʼֵ0x6363
	Write_MFRC522(CommandReg,0x00);			//����MFRC522  
	//Write_MFRC522(RFCfgReg, 0x7F);    //RxGain = 48dB���ڿ���Ӧ����      
	AntennaOn();          							//������ 
}
//��������??RC522��ISO14443��ͨѶ
//�������??command--MF522������
//					sendData--ͨ��RC522���͵���Ƭ������
//					sendLen--���͵����ݳ���
//					BackData--���յ��Ŀ�Ƭ��������
//					BackLen--�������ݵ�λ����
//�� �� ֵ?��ɹ�����MI_O
u8 MFRC522_ToCard(u8 command, u8 *sendData, u8 sendLen, u8 *backData, u16 *backLen) 
{
	u8  status=MI_ERR;
	u8  irqEn=0x00;
	u8  waitIRq=0x00;
	u8  lastBits;
	u8  n;
	u16 i;
	//������Ԥ���жϲ���
	switch (command)     
	{         
		case PCD_AUTHENT:  		//��֤����   
			irqEn 	= 0x12;			//    
			waitIRq = 0x10;			//    
			break;
		case PCD_TRANSCEIVE: 	//����FIFO������      
			irqEn 	= 0x77;			//    
			waitIRq = 0x30;			//    
			break;      
		default:    
			break;     
	}
	//
	Write_MFRC522(ComIEnReg, irqEn|0x80);		//�����ж�����     
	ClearBitMask(ComIrqReg, 0x80);  				//��������ж�����λ               	
	SetBitMask(FIFOLevelReg, 0x80);  				//FlushBuffer=1, FIFO��ʼ��
	Write_MFRC522(CommandReg, PCD_IDLE); 		//ʹMFRC522����   
	//��FIFO��д������     
	for (i=0; i<sendLen; i++)
		Write_MFRC522(FIFODataReg, sendData[i]);
	//ִ������
	Write_MFRC522(CommandReg, command);
	//���߷�������     
	if (command == PCD_TRANSCEIVE)					//����ǿ�Ƭͨ�����MFRC522��ʼ�����߷�������      
		SetBitMask(BitFramingReg, 0x80);  		//StartSend=1,transmission of data starts      
	//�ȴ������������     
	i = 10000; //i����ʱ��Ƶ�ʵ���?�����M1�����ȴ�ʱ��25ms     
	do      
	{        
		n = Read_MFRC522(ComIrqReg);
		//irq_regdata=n;	//test         
		i--;
		//wait_count=i;		//test		     
	}while ((i!=0) && !(n&0x01) && !(n&waitIRq));	//��������˳�n=0x64
	//ֹͣ����
	ClearBitMask(BitFramingReg, 0x80);   		//StartSend=0
	//�����25ms�ڶ�����
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
//��������?�Ѱ������ȡ�����ͺ?
//�������??reqMode--Ѱ����ʽ
//					TagType--���ؿ�Ƭ����
//					0x4400 = Mifare_UltraLight
//					0x0400 = Mifare_One(S50)
//					0x0200 = Mifare_One(S70)
//					0x0800 = Mifare_Pro(X)
//					0x4403 = Mifare_DESFire
//�� �� ֵ?��ɹ�����MI_OK	
u8 MFRC522_Request(u8 reqMode, u8 *TagType)
{  
	u8  status;    
	u16 backBits;   //���յ�������λ��
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
//��������?�����ͻ��⪡��ȡѡ�п��?�Ŀ����к�
//�������??serNum--����4�ֽڿ����к�,��5�ֽ�ΪУ���ֽ�
//�� �� ֵ?��ɹ�����MI_OK
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
		//У�鿨���к�   
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
//��������?���MF522����CRC
//�������??pIndata--Ҫ����CRC������??len--���ݳ���??pOutData--�����CRC���
void CalulateCRC(u8 *pIndata, u8 len, u8 *pOutData) 
{     
	u16 i;
	u8  n;
	//      
	ClearBitMask(DivIrqReg, 0x04);   			//CRCIrq = 0     
	SetBitMask(FIFOLevelReg, 0x80);   		//��FIFOָ��     
	Write_MFRC522(CommandReg, PCD_IDLE);   
	//��FIFO��д������      
	for (i=0; i<len; i++)
		Write_MFRC522(FIFODataReg, *(pIndata+i));
	//��ʼRCR����
	Write_MFRC522(CommandReg, PCD_CALCCRC);
	//�ȴ�CRC�������     
	i = 1000;     
	do      
	{         
		n = Read_MFRC522(DivIrqReg);         
		i--;     
	}while ((i!=0) && !(n&0x04));   //CRCIrq = 1
	//��ȡCRC������     
	pOutData[0] = Read_MFRC522(CRCResultRegL);     
	pOutData[1] = Read_MFRC522(CRCResultRegH);
	Write_MFRC522(CommandReg, PCD_IDLE);
}
//��������?�ѡ������ȡ���洢�����?
//�������??serNum--���뿨���к�
//�� �� ֵ?��ɹ����ؿ����?
u8 MFRC522_SelectTag(u8 *serNum) 
{     
	u8  i;     
	u8  status;     
	u8  size;     
	u16 recvBits;     
	u8  buffer[9];
	//     
	buffer[0] = PICC_ANTICOLL1;	//��ײ��1     
	buffer[1] = 0x70;
	buffer[6] = 0x00;						     
	for (i=0; i<4; i++)					
	{
		buffer[i+2] = *(serNum+i);	//buffer[2]-buffer[5]Ϊ�����к�
		buffer[6]  ^=	*(serNum+i);	//��У����
	}
	//
	CalulateCRC(buffer, 7, &buffer[7]);	//buffer[7]-buffer[8]ΪRCRУ����
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
//��������?���֤���?����
//�������??authMode--������֤ģʽ
//					0x60 = ��֤A��Կ
//					0x61 = ��֤B��Կ
//					BlockAddr--���ַ
//					Sectorkey--��������
//					serNum--��Ƭ���к�??4�ֽ�
//�� �� ֵ?��ɹ�����MI_OK
u8 MFRC522_Auth(u8 authMode, u8 BlockAddr, u8 *Sectorkey, u8 *serNum) 
{     
	u8  status;     
	u16 recvBits;     
	u8  i;  
	u8  buff[12];    
	//��֤ģʽ+���ַ+��������+�����к�     
	buff[0] = authMode;		//��֤ģʽ     
	buff[1] = BlockAddr;	//���ַ     
	for (i=0; i<6; i++)
		buff[i+2] = *(Sectorkey+i);	//��������
	//
	for (i=0; i<4; i++)
		buff[i+8] = *(serNum+i);		//�����к�
	//
	status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
	//      
	if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
		status = MI_ERR;
	//
	return status;
}
//��������?������?��
//�������??blockAddr--���ַ;recvData--�����Ŀ�����
//�� �� ֵ?��ɹ�����MI_OK
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
//��������?�д���?��
//�������??blockAddr--���ַ;writeData--���д16�ֽ�����
//�� �� ֵ?��ɹ�����MI_OK
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
		for (i=0; i<16; i++)  //��FIFOд16Byte����                     
			buff[i] = *(writeData+i);
		//                     
		CalulateCRC(buff, 16, &buff[16]);         
		status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);           
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))               
			status = MI_ERR;         
	}          
	return status;
}
//��������?��?�Ƭ��������״̬
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