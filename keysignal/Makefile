obj-m :=keysignal.o
KDIR := /work/linux/
CC = arm-linux-gcc
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
test:
	$(CC) -static testkeysignal.c -o testkeysignal
testcopy:
	cp -f testkeysignal /work/rootfs/work/
clean:
	rm *.o *.ko *.mod.c *.order *.symvers
copy:
	cp -f keysignal.ko /work/rootfs/work/
	cp -f testkeysignal /work/rootfs/work/
