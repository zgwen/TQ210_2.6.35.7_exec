/*************************************************************************
	> File Name: memdev.h
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Sat 11 Nov 2017 10:40:06 PM PST
 ************************************************************************/

#ifndef _MEMDEV_H
#define _MEMDEV_H
#define MEM_MAGIC 'm'
#define MEM_RESTART _IO(MEM_MAGIC,1)
#define MEM_SET _IOW(MEM_MAGIC,2,int)
#endif
