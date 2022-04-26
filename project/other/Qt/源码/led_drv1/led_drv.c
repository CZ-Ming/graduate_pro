//D8---C17, D9---C8,  D10---C7,  D11---C12
//GPIOCOUT    --->0xC001C000 ---设置引脚的输出数值
//GPIOCOUTENB --->0xC001C004 ----设置引脚是输入引脚还是输出引脚：1为输出引脚，0位输入引脚.
//GPIOCALTFN0 --->0xC001C020设置[15:0]引脚的功能：
//GPIOCALTFN1 --->0xC001C024设置[31:16]引脚的功能：2.3 GPIO function description


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/device.h>

//1. 定义一个字符设备
static struct cdev led_dev;

//定义设备号
static unsigned int led_major = 0;
static unsigned int led_minor = 0;
static dev_t led_num;

struct resource * led_res;
void __iomem *GPIOCOUT_VA;
void __iomem *GPIOCOUTENB_VA;
void __iomem *GPIOCALTFN0_VA;
void __iomem *GPIOCALTFN1_VA;

static struct class *led_class;
static struct device *led_device; 
//3.定义文件操作集，并作详细初始化

//应用程序写下来的数据分成2个字节，buf[0]-->led的状态：0--led off， 1--led on
                                 //buf[1]-->哪一盏灯：8~11.
ssize_t gec6818_led_write(struct file *filp, const char __user *buf, size_t len, loff_t *off_size)
{
	//驱动程序接收应用程序写下来的数据，并用这些数据控制led的状态
	char kbuf[2];
	int ret;
	if(len != 2)
		return -EINVAL;
	ret = copy_from_user(kbuf, buf, len);
	if(ret != 0)
		return -EFAULT;
	//printk("kbuf[1]=%d, kbuf[0]= %d\n", kbuf[1],kbuf[0]);
	if(kbuf[0] == 1)//led on
		switch(kbuf[1]){
		case 11: //D11-->GPIOC12
			writel(readl(GPIOCOUT_VA)& ~(1<<12), GPIOCOUT_VA);
			break;
		case 10: //D10-->GPIOC7
			writel(readl(GPIOCOUT_VA)& ~(1<<7), GPIOCOUT_VA);
			break;	
		case 9:  //D9-->GPIOC8
			writel(readl(GPIOCOUT_VA)& ~(1<<8), GPIOCOUT_VA);
			break;	
		case 8:  //D8-->GPIOC17
			writel(readl(GPIOCOUT_VA)& ~(1<<17), GPIOCOUT_VA);
			break;
		default:
			return -EFAULT;
		}
	else if(kbuf[0] == 0)//led off
		switch(kbuf[1]){
		case 11: //D11-->GPIOC12
			writel(readl(GPIOCOUT_VA)|(1<<12), GPIOCOUT_VA);
			break;
		case 10: //D10-->GPIOC7
			writel(readl(GPIOCOUT_VA)|(1<<7), GPIOCOUT_VA);
			break;	
		case 9:  //D9-->GPIOC8
			writel(readl(GPIOCOUT_VA)|(1<<8), GPIOCOUT_VA);
			break;	
		case 8:  //D8-->GPIOC17
			writel(readl(GPIOCOUT_VA)|(1<<17), GPIOCOUT_VA);
			break;
		default:
			return -EFAULT;
		}
	else
		return -EFAULT;

	return len;
}


static const struct file_operations led_fops = {
	.owner = THIS_MODULE, 
	.write = gec6818_led_write,
};


static int __init gec6818_led_init(void)
{
	int ret;
	int temp;
	//2.申请设备号
	if(led_major==0)
		ret = alloc_chrdev_region(&led_num, led_minor, 1,"led_dev");
	else{
		led_num = MKDEV(led_major, led_minor);
		ret = register_chrdev_region(led_num,1,"led_dev");
	}
	if(ret < 0){
		printk("can not get a device number\n");
		return ret;
	}
	
	//4. 字符设备的初始化
	cdev_init(&led_dev, &led_fops);
	
	//5.将字符设备加入内核
	ret = cdev_add(&led_dev, led_num, 1);
	if(ret < 0){
		printk("cdev add  error\n");
		//unregister_chrdev_region(led_num, 1);
		//return ret;
		goto  cdev_add_error;
	}
	//6. 创建class
	led_class = class_create(THIS_MODULE, "gec6818_led");
	if(IS_ERR(led_class)) {
		printk("Err: failed in creating class.\n");
		ret = -EBUSY;
		goto class_create_err;
	}
	
	//7. 创建device----生成的设备文件---/dev/led_drv
	led_device = device_create(led_class, NULL,led_num, NULL,"led_drv");
	if(IS_ERR(led_device)) {
		printk("Err: failed in creating device.\n");
		ret = -EBUSY;
		goto device_create_err;
	}
	
	//8. 申请物理内存区
	led_res = request_mem_region(0xC001C000, 1024*4,  "GPIOC_LED");
	if(led_res == NULL){
		printk("can not request GPIOC_LED\n");
		ret = -EBUSY;
		goto request_mem_err;
	}
	//8.IO内存的动态映射，得到虚拟地址
	GPIOCOUT_VA = ioremap(0xC001C000, 1024*4);
	if(GPIOCOUT_VA == NULL){
		printk("ioremap error \n");
		ret = -EFAULT;
		goto ioremap_err;
	}
	
	GPIOCOUTENB_VA = GPIOCOUT_VA + 0x04;
	GPIOCALTFN0_VA = GPIOCOUT_VA + 0x20;
	GPIOCALTFN1_VA = GPIOCOUT_VA + 0x24;
	printk("cout_va=%p,coutenb_va=%p\n, caltfn0=%p\n", GPIOCOUT_VA, GPIOCOUTENB_VA, GPIOCALTFN0_VA);
	
	//将GPIO初始化为输出
	temp = readl(GPIOCALTFN0_VA) & (~((3<<24)|(3<<16)|(3<<14)));
	temp |= ((1<<24)|(1<<16)|(1<<14));
	writel(temp, GPIOCALTFN0_VA);
	
	temp = readl(GPIOCALTFN1_VA) & (~(3<<2));
	temp |= (1<<2);
	writel(temp, GPIOCALTFN1_VA);
	
	temp = readl(GPIOCOUTENB_VA) | ((1<<17)|(1<<12)|(1<<8)|(1<<7));
	writel(temp, GPIOCOUTENB_VA);
	
	temp = readl(GPIOCOUT_VA) | ((1<<17)|(1<<12)|(1<<8)|(1<<7));
	writel(temp, GPIOCOUT_VA);
	
	printk("gec6818 led driver init....\n");
	return 0;
	
ioremap_err:
	release_mem_region(0xC001C000, 1024*4);
request_mem_err:
	device_destroy(led_class, led_num);
device_create_err:
	class_destroy(led_class);
class_create_err:
	cdev_del(&led_dev);	
cdev_add_error:
	unregister_chrdev_region(led_num, 1);
	return ret;
}

static void __exit gec6818_led_exit(void)
{
	device_destroy(led_class, led_num);
	class_destroy(led_class);
	iounmap(GPIOCOUT_VA);
	release_mem_region(0xC001C000, 1024*4);
	unregister_chrdev_region(led_num, 1);
	cdev_del(&led_dev);
	printk("gec6818 remove led driver\n");
}


//入口和出口
module_init(gec6818_led_init); //入口
module_exit(gec6818_led_exit); //出口

//驱动的描述，可选的
MODULE_AUTHOR("bobeyfeng@163.com");
MODULE_DESCRIPTION("gec6818 led driver");
MODULE_VERSION("V1.0");
MODULE_LICENSE("GPL");//驱动程序符合的协议