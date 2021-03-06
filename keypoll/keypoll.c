/*************************************************************************
	> File Name: keyloop.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Tue 14 Nov 2017 03:16:32 AM PST
 ************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
//#include <mach/regs-gpio.h>
//#include <mach/hardware.h>

static struct class *key_class;
static struct device *key_class_dev;

static DECLARE_WAIT_QUEUE_HEAD(my_key_waitq);
//中断按键按下标志
static volatile int key_pressed = 0;

struct pin_desc{
    unsigned int pin;
    unsigned char key_val;
};
struct pin_desc pins_desc[4] = {
    {S5PV210_GPH0(4),0x05},
    {S5PV210_GPH0(5),0x06},
    {S5PV210_GPH2(6),0x07},
    {S5PV210_GPH2(7),0x08},
};

//按键值
static unsigned char key_val;

//中断处理函数
static irqreturn_t key_eint_handler(int irq, void *desc)
{
    unsigned int pin_level;
    struct pin_desc *key_desc;
    key_desc = (struct pin_desc *) desc;
    pin_level = gpio_get_value(key_desc->pin);
    //此判断纯属扯淡
    if(!pin_level)
        key_val = key_desc->key_val;
    else
        printk("key_level error!");

    key_pressed = 1;
    wake_up_interruptible(&my_key_waitq);



    return IRQ_RETVAL(IRQ_HANDLED);
}

int key_open(struct inode *inode, struct file *filp)
{
    int ret;
    //初始化IRQ，同时初始化相关引脚
    ret = request_irq(IRQ_EINT(4),key_eint_handler,IRQ_TYPE_EDGE_FALLING,"my_key4",&pins_desc[0]);
    if(ret)
    return ret;
    ret = request_irq(IRQ_EINT(5),key_eint_handler,IRQ_TYPE_EDGE_FALLING,"my_key5",&pins_desc[1]);
    if(ret)
        return ret;
    ret = request_irq(IRQ_EINT(22),key_eint_handler,IRQ_TYPE_EDGE_FALLING,"my_key7",&pins_desc[2]);
    if(ret)
        return ret;
    ret = request_irq(IRQ_EINT(23),key_eint_handler,IRQ_TYPE_EDGE_FALLING,"my_key8",&pins_desc[3]);
    if(ret)
        return ret;

    return 0;
}

static ssize_t key_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    if(size != 1)
        return -EINVAL;
    wait_event_interruptible(my_key_waitq,key_pressed);

    //copy_to_user数据拷贝成功则返回0,read失败返回0
    if(copy_to_user(buf,&key_val,1))
        return 0; 
    key_pressed = 0;

    return 1;
}

//poll函数
unsigned int  key_poll(struct file *filp, struct poll_table_struct *wait)
{
    unsigned int mask = 0;

    //进入睡眠队列定时等待
    poll_wait(filp,&my_key_waitq,wait);

    if(key_pressed)
    {
        //返回可读标志，POLLIN和POLLRDNORM等效
        mask = POLLIN | POLLRDNORM;
    }    

    return mask;

}

int key_close(struct inode *inod, struct file *filp)
{
    free_irq(IRQ_EINT(4),&pins_desc[0]);
    free_irq(IRQ_EINT(5),&pins_desc[1]);
    free_irq(IRQ_EINT(22),&pins_desc[2]);
    free_irq(IRQ_EINT(23),&pins_desc[3]);
    return 0;    
}

static struct file_operations key_fops = 
{
    .owner = THIS_MODULE,  //这是一个宏，指向编译模块时自动创建的_this_module变量
    .open = key_open,
    .read = key_read,
    .release = key_close,
    .poll = key_poll,
};
int major;//主设备号
static int mykey_init(void)
{
    //创建设备，自动分配主设备号
    major = register_chrdev(0,"keypoll_drv",&key_fops);
    //两部自动创建设备节点
    //1.创建设备类，可在/sys/class目录下查看该类文件夹
    key_class = class_create(THIS_MODULE,"keypoll_drv");
    //2.在/dev目录下创建节点
    key_class_dev = device_create(key_class,NULL,MKDEV(major,0),NULL,"key_poll"); 

    return 0;
}

static void mykey_exit(void)
{
    unregister_chrdev(major,"keypoll_drv");
    device_unregister(key_class_dev);
    class_destroy(key_class);
}

MODULE_LICENSE("GPL");

module_init(mykey_init);
module_exit(mykey_exit);
