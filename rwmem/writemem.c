/*************************************************************************
	> File Name: writemem.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Sun 29 Oct 2017 12:31:37 AM PDT
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd;
    const char *pathname="/dev/vmemdev0";
    int buf[2];
    buf[0]=1995;
    buf[1]=222;
    fd=open(pathname,O_RDWR);
    write(fd,buf,2*sizeof(int));
    //write(fd,&buf[0]+1,sizeof(int));
    close(fd);
    return 0;
}
