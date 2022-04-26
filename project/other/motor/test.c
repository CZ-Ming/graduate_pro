/*---------------------------------------
*功能描述:  蜂鸣器测试程序 
*创建者：   粤嵌技术部
*创建时间： 2015,01,01
---------------------------------------
*修改日志：
*修改内容：
*修改人：
*修改时间：
----------------------------------------*/
/*************************************************
*头文件
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define CDM_MOTOR_HIGH   	_IOW('L',0,unsigned long)
#define CDM_MOTOR_LOW  		_IOW('L',1,unsigned long)
#define CDM_MOTOR_CLOSE  	_IOW('L',2,unsigned long)

int main(void)
{
	int fd;
	int ret;
	fd = open("/dev/motor", O_RDWR);            //打开设备，成功返回0
	if(fd<0){
		perror("open:");
		return -1;
	}
//关门
	int i =20;
	while(i--) {
	
		ioctl(fd, CDM_MOTOR_CLOSE, 1);                //BUZZER off	
	}	


	close(fd);
	return 0;
}
