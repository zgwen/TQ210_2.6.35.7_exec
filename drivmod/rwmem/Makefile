writemem:readmem writemem.c
	arm-linux-gcc -static -o writemem  writemem.c
readmem:readmem.c
	arm-linux-gcc -static -o readmem readmem.c
clean:
	rm -f writemem readmem *.o *.ko *.mod.c *.order *.symvers
copy:
	cp -f  writemem readmem /work/rootfs/work/
