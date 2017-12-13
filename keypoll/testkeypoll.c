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
void main(void)
{
    unsigned int fd;
    unsigned char key_val;
    //定义文件描述符结构体数组
    struct pollfd fds[1];

    fd = open("/dev/key_poll",O_RDWR);

    fds[0].fd = fd;
    //定义poll感兴趣的事件
    fds[0].events = POLLIN;

    while(1)
    {
        if(poll(&fds[0],1,5000) == POLLIN)
        {
            if(!read(fd,&key_val,1))
                printf("read error!\n");
            else
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
        else
        {
            printf("time out!\n");
        }
    }
}
