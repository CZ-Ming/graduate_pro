obj-m+=mfrc_drv.o
mfrc_drv-objs=MFRC522.o mfrc522_drv.o


KERNEL_DIR:=/home/gec/6818GEC/kernel
CROSS_COMPILE:=/home/gec/6818GEC/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
PWD:=$(shell pwd)

default:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) modules
	arm-linux-gcc test.c -o t
	make clean
clean:
	rm *.o *.order .*.cmd *.mod.c *.symvers *.tmp_versions -rf




