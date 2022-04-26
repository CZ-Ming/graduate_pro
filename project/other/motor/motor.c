#include <linux/module.h>
#include <linux/fs.h>//register_chrdev_region
#include <linux/cdev.h>
#include <linux/uaccess.h>//copy_to_from_user

#include <linux/gpio.h>
#include <mach/platform.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#define CDM_MOTOR_HIGH   	_IOW('L',0,unsigned long)
#define CDM_MOTOR_LOW  		_IOW('L',1,unsigned long)
#define CDM_MOTOR_CLOSE  	_IOW('L',2,unsigned long)

static struct gpio motors_gpios[]={
	{ PAD_GPIO_E + 13, GPIOF_OUT_INIT_HIGH, "motor" }, /* default to ON */

};




int motor_open (struct inode *inode, struct file *file)
{

	printk(KERN_INFO"motor open\n");
	return 0;
}

int motor_close (struct inode *inode, struct file *files)
{


	gpio_set_value(motors_gpios[0].gpio, 0);

	printk(KERN_INFO"motor close\n");
	return 0;
}

long motor_ioctl (struct file *file, unsigned int cmd, unsigned long args)
{

	if(args!=1) {
		printk("the args is out of range 1 \n");
		return -EINVAL;
	}


	switch(cmd)
	{
		case CDM_MOTOR_CLOSE:
		{
			gpio_set_value(motors_gpios[0].gpio, 1);
			mdelay(1);
			gpio_set_value(motors_gpios[0].gpio, 0);
			mdelay(19);
		}break;
		
		case CDM_MOTOR_HIGH:
		{
			gpio_set_value(motors_gpios[0].gpio, 1);
		}break;

		case CDM_MOTOR_LOW:
		{
			gpio_set_value(motors_gpios[0].gpio, 0);
		}break;

		default:
		{
			return -EINVAL; 
		}break;

	}

	return 0;


}



static struct file_operations motor_fops =
{
	.open = motor_open,
	.release = motor_close,
	.unlocked_ioctl = motor_ioctl,
};

static struct miscdevice motor_miscdev=
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "motor",
	.fops = &motor_fops,

};


static int __init motor_init(void)
{
	int rt = 0;

	printk(KERN_INFO"motor init\n");

	
	rt = misc_register(&motor_miscdev);
	if(rt < 0)
	{
		printk(KERN_ERR"misc_register err\n");
		goto err_misc_register;
	}
	
	gpio_free_array(motors_gpios, ARRAY_SIZE(motors_gpios));
	
	rt = gpio_request_array(motors_gpios, ARRAY_SIZE(motors_gpios));
	if(rt<0)
		goto err_gpio_request_array;
	
	return 0;

err_gpio_request_array:
	misc_deregister(&motor_miscdev);

err_misc_register:

	return rt;
}

static void __exit motor_exit(void)
{
	gpio_free_array(motors_gpios, ARRAY_SIZE(motors_gpios));

	misc_deregister(&motor_miscdev);
	printk(KERN_INFO"motor exit\n");

}



module_init(motor_init);
module_exit(motor_exit);

MODULE_AUTHOR("CZM");
MODULE_DESCRIPTION("motor Driver");
MODULE_LICENSE("GPL");

















