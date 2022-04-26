#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[2];
	int ret;
	fd = open("/dev/led_drv", O_WRONLY);
	if(fd<0)
	{
		perror("open");
		return -1;
	}
  while(1)
  {  
	buf[1]=8; buf[0]=1; //led2 on
	ret = write(fd,buf,2);
	if(ret !=2 )
		perror("write");
	sleep(1);
	buf[1]=8; buf[0]=0;//led2 off
	ret = write(fd,buf,2);
	if(ret !=2 )
		perror("write");
	sleep(1);
  }
	close(fd);
	return 0;
}