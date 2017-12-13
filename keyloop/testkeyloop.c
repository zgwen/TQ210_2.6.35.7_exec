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
    unsigned char kval[4];
    fd = open("/dev/key_loop",O_RDWR);
    while(1)
    {
        read(fd,kval,sizeof(kval));
        if(!(kval[1] && kval[2] && kval[3] && kval[0]))
        {
            usleep(100000);
            if(!(kval[1] && kval[2] && kval[3] && kval[0]))
                if(!kval[0])
                    printf("KEY1 pressed!\n");
                else if (!kval[1])
                    printf("KEY2 pressed!\n");
                else if (!kval[2])
                    printf("KEY3 pressed!\n");
                else
                    printf("KEY4 pressed!\n");
        }
        usleep(100000);

    }
}
