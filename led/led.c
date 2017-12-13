/*************************************************************************
	> File Name: led.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Mon 13 Nov 2017 03:16:23 AM PST
 ************************************************************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/io.h>
//#include <mach/gpio-bank-k.h>
#include "led.h"

struct cdev *pdev;
dev_t devnm;
unsigned int *led_config;
unsigned int *led_data;

int led_open(struct inode *inode,struct file *filp)
{
    if(MINOR(inode->i_rdev)!=0)
        return -ENODEV;
    led_config = ioremap(GPC0CON,4);
    writel(0x11000,led_config);
    led_data = ioremap(GPC0DAT,4);
    writel(0x18,led_data);
    return 0;
}

long led_ctrl(struct file *filp,unsigned int cmd, unsigned long args)
{
    switch (cmd)
    {
        case LED_ON:
            //printk("led on\n");
            writel(0x18,led_data);
            return 0;
        case LED_OFF:
            //printk("led off\n");
            writel(0x00,led_data);
            return 0;
        default:
            return -EINVAL;
    }
}
static const struct file_operations led_fpos=
{
    .open = led_open,
    .unlocked_ioctl = led_ctrl,
};

static void led_init(void)
{
    pdev=cdev_alloc();
    cdev_init(pdev,&led_fpos);
    alloc_chrdev_region(&devnm,0,1,"leddev");
    cdev_add(pdev,devnm,1);
}

static void led_exit(void)
{
    cdev_del(pdev);
    unregister_chrdev_region(devnm,1);
}

MODULE_LICENSE("GPL");

module_init(led_init);
module_exit(led_exit);

