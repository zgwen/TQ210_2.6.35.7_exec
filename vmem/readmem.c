/*************************************************************************
	> File Name: readmem.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Sun 29 Oct 2017 12:55:11 AM PDT
 ************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd;
    int buf[2];
    const char *pathname="/dev/vmemdev0";
    fd=open(pathname,O_RDWR);
    read(fd,buf,2*sizeof(int));
    printf("The num is %4d %4d\n",buf[0],buf[1]);
    close(fd);
    return 0;
}
