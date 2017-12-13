obj-m :=keyeint.o
KDIR := /work/linux/
CC = arm-linux-gcc
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
test:
	$(CC) -static testkeyeint.c -o testkeyeint
testcopy:
	cp -f testkeyeint /work/rootfs/work/
clean:
	rm *.o *.ko *.mod.c *.order *.symvers
copy:
	cp -f keyeint.ko /work/rootfs/work/
