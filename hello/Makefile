obj-m := hellomodule.o

KDIR :=/work/linux/

all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
clean:
	rm -f *.o *.ko *.order *.symvers *.mod.c
