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
#include<signal.h>


unsigned int fd;
//信号处理函数
void key_signal_func(int signum)
{
    unsigned char key_val;
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

void main(void)
{
    int Oflags;

    //注册信号处理函数
    signal(SIGIO,key_signal_func);
    //打开设备，获取设备fd
    fd = open("/dev/key_signal",O_RDWR);

    //设置fd接收信号的进程ID
    fcntl(fd,F_SETOWN,getpid());
    //获取fd的所有文件标志
    Oflags = fcntl(fd,F_GETFL);
    //为fd的文件描述符增加FASYNC标志，驱动中会调用.fasync函数
    fcntl(fd,F_SETFL,Oflags | FASYNC);
    while(1)
    {
       sleep(3000);
    }
}
