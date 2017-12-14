obj-m :=keysemaphore.o
KDIR := /work/linux/
CC = arm-linux-gcc
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
test:
	$(CC) -static testkeysemaphore.c -o testkeysemaphore
testcopy:
	cp -f testkeysemaphore /work/rootfs/work/
clean:
	make -C $(KDIR) M=$(PWD) modules clean
copy:
	cp -f keysemaphore.ko /work/rootfs/work/
	cp -f testkeysemaphore /work/rootfs/work/
