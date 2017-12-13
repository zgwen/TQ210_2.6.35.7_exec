obj-m :=led.o
KDIR := /work/linux/
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
clean:
	rm *.o *.ko *.mod.c *.order *.symvers
copy:
	cp -f led.ko /work/rootfs/work/
