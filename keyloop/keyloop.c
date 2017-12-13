/*************************************************************************
	> File Name: keyloop.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Tue 14 Nov 2017 03:16:32 AM PST
 ************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
//#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
//#include <mach/regs-gpio.h>
//#include <mach/hardware.h>
volatile unsigned long *gph0con;
volatile unsigned long *gph0dat;

static struct class *key_class;
static struct device *key_class_dev;

int key_open(struct inode *inode, struct file *filp)
{
    //配置GPH0_0,1,2,3为输出引脚
    *gph0con = (*gph0con & (~0xffff)) | 0x01 | (0x00<<4) | (0x00<<8) | (0x00<<12);
    return 0;
}

static ssize_t key_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    unsigned char kval[4];

    if(size != sizeof(kval))
        return -EINVAL;

    kval[0]=(*gph0dat & 0x01) ? 1 : 0;
    kval[1]=(*gph0dat & 0x02) ? 1 : 0;
    kval[2]=(*gph0dat & 0x04) ? 1 : 0;
    kval[3]=(*gph0dat & 0x08) ? 1 : 0;

    if(copy_to_user(buf,kval,sizeof(kval))!=sizeof(kval))
        return -1;

    return sizeof(kval);

}

static struct file_operations key_fops = 
{
    .owner = THIS_MODULE,  //这是一个宏，指向编译模块时自动创建的_this_module变量
    .open = key_open,
    .read = key_read,
};
int major;//主设备号
int  key_init(void)
{
    //创建设备，自动分配主设备号
    major = register_chrdev(0,"keyloop_drv",&key_fops);
    //两部自动创建设备节点
    //1.创建设备类，可在/sys/class目录下查看该类文件夹
    key_class = class_create(THIS_MODULE,"keyloop_drv");
    //2.在/dev目录下创建节点
    key_class_dev = device_create(key_class,NULL,MKDEV(major,0),NULL,"key_loop"); 

    //映射io地址
    gph0con = (volatile unsigned long *)ioremap(0xE0200C00,8);
    gph0dat = gph0con + 1;

    return 0;
}

void key_exit(void)
{
    unregister_chrdev(major,"keyloop_drv");
    device_unregister(key_class_dev);
    class_destroy(key_class);
    //取消io映射
    iounmap(gph0con);
}

MODULE_LICENSE("GPL");

module_init(key_init);
module_exit(key_exit);
