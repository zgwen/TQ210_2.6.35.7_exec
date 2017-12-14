/*************************************************************************
	> File Name: testkeyloop.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Thu 16 Nov 2017 03:40:31 AM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<poll.h>


int fd;

int  main(int argc, char *argv)
{
    unsigned char key_val;
    int ret;
    //打开设备，获取设备fd
    if((fd = open("/dev/key_semaphore",O_RDWR | O_NONBLOCK)) < 0 )
    {
        printf("Open error!\n");
        return -1;
    }
    while(1)
    {
        if(read(fd,&key_val,1) < 0)
        {
            printf("Please press any key!\n");
            sleep(5);
        }
        else
        {
            switch (key_val)
            {
                case 0x05: 
                    printf("Enter pressed!\n");
                    break;
                case 0x06: 
                    printf("Home pressed!\n");
                    break;
                case 0x07: 
                    printf("Esc pressed!\n");
                    break;
                case 0x08: 
                    printf("Power pressed!\n");
                    break;
                default:
                    printf("wait error!");
            }
        
    }
}
