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
void main(void)
{
    unsigned int fd;
    unsigned char key_val;
    fd = open("/dev/key_eint",O_RDWR);
    while(1)
    {
        read(fd,&key_val,1);
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
