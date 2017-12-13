/*************************************************************************
	> File Name: led_app.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Mon 13 Nov 2017 04:49:11 AM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include"led.h"

int main(int argc, char *argv[])
{
    int fd;
    int cmd;
    if(argc < 2)
    {
        printf("please enter the second para!\n");
        return 0;
    }
    cmd = atoi(argv[1]);
    fd = open("/dev/leddev",O_RDWR);
    if(cmd == 1)
        ioctl(fd,LED_ON);
    else if(cmd == 0)
        ioctl(fd,LED_OFF);
    else if (cmd == 3)
        while(1)
    {
        //mdelay(500);
        sleep(1);
        ioctl(fd,LED_ON);
        sleep(1);
        ioctl(fd,LED_OFF);
    }
    return 0;
}
