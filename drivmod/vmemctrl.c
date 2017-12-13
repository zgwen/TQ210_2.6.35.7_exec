/*************************************************************************
	> File Name: vmemctrl.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Sat 11 Nov 2017 11:21:56 PM PST
 ************************************************************************/

#include<stdio.h>
#include "vmem.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main()
{
    int fd;
    fd = open("/dev/vmemdev0",O_RDWR);
    ioctl(fd,MEM_RESTART);
    ioctl(fd,MEM_SET,19950222);
    close(fd);
    return 0;
}
