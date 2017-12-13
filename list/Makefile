obj-m := mylist.o
KDIR := /work/linux/ 
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
clean:
	rm *.o *.ko *.mod.c *.order *.symvers 
copy:
	cp -f  mylist.ko /work/rootfs/work
