obj-m :=keypoll.o
KDIR := /work/linux/
CC = arm-linux-gcc
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
test:
	$(CC) -static testkeypoll.c -o testkeypoll
testcopy:
	cp -f testkeypoll /work/rootfs/work/
clean:
	rm *.o *.ko *.mod.c *.order *.symvers
copy:
	cp -f keypoll.ko /work/rootfs/work/
	cp -f testkeypoll /work/rootfs/work/
