

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/gpio.h>

#include "MFRC522.h"


/*
SDA --MCU_SPIFRM0--c30----9
SCK --MCU_SPICLK0--c29---7
MOSI--MCU_SPITXD0--c31---11
MISO--MCU_SPIRXD0--d0---13
IRQ
GND--gnd---19
RST--GPIOC7---15
3V3--3v3---1
*/


#define CMD_RFID_WR   _IOW('R',0,unsigned int)
#define CMD_RFID_RD   _IOR('R',0,unsigned int)
#define CMD_RFID_RDID _IOR('R',1,unsigned int)


static struct gpio mfrc522_gpios[] ={
	{PAD_GPIO_C+29,GPIOF_OUT_INIT_HIGH,"MFRC522 SCLK"},
	{PAD_GPIO_C+30,GPIOF_OUT_INIT_HIGH,"MFRC522 SDA"},
	{PAD_GPIO_C+31,GPIOF_OUT_INIT_HIGH,"MFRC522 MOSI"},
	{PAD_GPIO_D+0 ,GPIOF_IN   	 	  ,"MFRC522 MISO"},
	{PAD_GPIO_C+7 ,GPIOF_OUT_INIT_HIGH,"MFRC522 RST"},
};


int mfrc522_open (struct inode *inode , struct file *file)
{

	printk(KERN_INFO"mfrc522_open \n");
	MFRC522_Initializtion();	

	return 0;
}



int mfrc522_close (struct inode *inode , struct file *file)
{

	int i=0;
	
	//应用层退出的时候，灯熄灭
	for(i=0; i<ARRAY_SIZE(mfrc522_gpios); i++)
		gpio_set_value(mfrc522_gpios[i].gpio, 1);


	printk(KERN_INFO"mfrc522_close \n");

	return 0;

}

long mfrc522_ioctl(struct file *file, unsigned int cmd, unsigned long args)
{

	void __user*argp = (void __user *)args;
	char buf[32];

	
	if(_IOC_TYPE(cmd)!='R')
		return -EINVAL;
	switch(cmd)
	{
		case CMD_RFID_WR:
		{
			if(copy_from_user(buf,argp,16))
				return -EFAULT;
			
			MFRC522_Initializtion();	
			mfrc_write(buf);
		}break;
		

		case CMD_RFID_RD:
		{
			MFRC522_Initializtion();	
			mfrc_read(buf);
			if(copy_to_user(argp,buf,16))
				return -EFAULT;
			
		}break;

		case CMD_RFID_RDID:
		{
			MFRC522_Initializtion();	
			mfrc_read_id((unsigned char *)buf);

			if(copy_to_user(argp,(unsigned char *)buf,5))
				return -EFAULT;
			
		}break;


		default:
			return -ENOIOCTLCMD;

	}


	return 0;

}



static struct file_operations mfrc522_fops=
{
	.open = mfrc522_open,
	.release = mfrc522_close,
	.unlocked_ioctl = mfrc522_ioctl,
};



static struct miscdevice misc_mfrc522 = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "mfrc522_dev",
	.fops  = &mfrc522_fops,
};



static int __init mfrc522_init(void)
{

	int ret =0;

	ret = misc_register(&misc_mfrc522);
	if(ret<0)
	{
		printk(KERN_ERR"misc_register \n");	
		goto err_misc_register;
	}

	gpio_free_array(mfrc522_gpios, ARRAY_SIZE(mfrc522_gpios));

	ret = gpio_request_array(mfrc522_gpios, ARRAY_SIZE(mfrc522_gpios));
	if(ret<0)
	{
		printk(KERN_ERR"gpio_request_array \n");	
		goto err_gpio_request_array;
	}


	printk(KERN_INFO"mfrc522_init \n");
	return 0;

err_gpio_request_array:
	misc_deregister(&misc_mfrc522);


err_misc_register:
	return ret;

}


static void __exit mfrc522_exit(void)
{
	gpio_free_array(mfrc522_gpios, ARRAY_SIZE(mfrc522_gpios));

	misc_deregister(&misc_mfrc522);

	printk(KERN_INFO"mfrc522_exit \n");

}



module_init(mfrc522_init);
module_exit(mfrc522_exit);

MODULE_AUTHOR("my mfrc522 drv");
MODULE_DESCRIPTION("this is mfrc522 drv");
MODULE_LICENSE("GPL");









