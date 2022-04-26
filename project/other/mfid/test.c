#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>


#define CMD_RFID_WR _IOW('R',0,unsigned int)
#define CMD_RFID_RD _IOR('R',0,unsigned int)



//”√”⁄≤‚ ‘
unsigned char   card_writebuf[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//u8  card_readbuf[18];

int main(int argc,char ** argv)
{

	char buf[32];
	int i =0;

    int fd = open("/dev/mfrc522_dev",O_RDWR);
    if(fd<0)
    {
        perror("mfrc522 open err!");
        return -1;
    }


	while(1)
	{
		sleep(1);
		memset(buf,0,sizeof(buf));
		//ioctl(fd,CMD_RFID_WR,card_writebuf);
		ioctl(fd,CMD_RFID_RD,buf);

		
		printf("card read: ");
		for(i =0 ;i<16;i++)
		{
			printf("%x ",buf[i]);
		}

		printf("\n");	

	}
		
    close(fd);

	return 0;

}
