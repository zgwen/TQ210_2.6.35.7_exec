obj-m :=keytimer.o
KDIR := /work/linux/
CC = arm-linux-gcc
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
test:
	$(CC) -static testkeytimer.c -o testkeytimer
testcopy:
	cp -f testkeytimer /work/rootfs/work/
clean:
	make -C $(KDIR) M=$(PWD) modules clean
copy:
	cp -f keytimer.ko /work/rootfs/work/
	cp -f testkeytimer /work/rootfs/work/
