#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include "vmem.h"
int dev1_reg[8];
int dev2_reg[8];

struct cdev *pdev; 
dev_t devnm;
//static struct class *memclass;

int vmem_open(struct inode *inode,struct file *flip)
{
    int num = MINOR(inode->i_rdev);
    if(num==0)
    {
        flip->private_data = dev1_reg;
    }
    else if(num==1)
    {
        flip->private_data = dev2_reg;
    }
    else
    {
        return -ENODEV;
    }

    return 0;
}

int vmem_release(struct inode *inode,struct file *filp)
{
    return 0;
}

static ssize_t vmem_read(struct file *flip,char __user *buf,size_t size,loff_t *ppos)
{
    loff_t p=*ppos;
    size_t count = size;
    int ret=0;    
    int *base_addr = flip->private_data;

    if(p >= 8*sizeof(int)) 
        return 0;
    if(count > 8*sizeof(int)-p)
        count = 8*sizeof(int)-p;

    if(copy_to_user(buf,base_addr+p,count))
        ret = -EFAULT;
    else
    {
        *ppos+=count;
        ret=count;
    }
    return ret;
}

static ssize_t vmem_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
    loff_t p=*ppos;
    size_t count=size;
    int ret=0;
    int *base_addr=filp->private_data;

    if(p>8*sizeof(int))
        return 0;
    if(count>8*sizeof(int)-p)
    {
        count=8*sizeof(int)-p;
    }

    if(copy_from_user(base_addr+p,buf,count))
        ret= -EFAULT;
    else
    {
        *ppos += count;
        ret=count;
    }
    return ret;

}

static loff_t vmem_llseek(struct file *filp,loff_t offset,int whence)
{
    loff_t newpos;
    switch(whence)
    {
        case SEEK_SET:
            newpos= offset;
            break;
        case SEEK_CUR:
            newpos= filp->f_pos+offset;
            break;
        case SEEK_END:
            newpos= 8*sizeof(int)-1+offset;
            break;
        default:
            return -EINVAL;
    }
    if((newpos<0)||(newpos>8*sizeof(int)))
        return -EINVAL;

    filp->f_pos= newpos;
    return newpos;
}
long vmem_ctrl(struct file *flip, unsigned int cmd, unsigned long args)
{
    switch (cmd)
    {
        case MEM_RESTART:
            printk("Memdev restarting...");
            return 0;
        case MEM_SET:
            printk("Memdev arg is %d",args);
            return 0;
        default:
            return -EINVAL;

    }
}

static const struct file_operations vmem_fpos=
{
    .llseek = vmem_llseek,
    .read = vmem_read,
    .write = vmem_write,
    .open = vmem_open,
    .release = vmem_release,
    .unlocked_ioctl = vmem_ctrl,
};

static int  memdev_init(void)
{
    pdev=cdev_alloc();
    cdev_init(pdev,&vmem_fpos);
    alloc_chrdev_region(&devnm,0,2,"vmemdev");
    cdev_add(pdev,devnm,2);
    //creat dev files
    //memclass=class_create(THIS_MODULE,"vmemdev");

    return 0;
    //device_create(memclass,NULL,devnm,NULL,"vmemdev0");
}

static void memdev_exit(void)
{
    cdev_del(pdev);
    unregister_chrdev_region(devnm,2);
}


MODULE_LICENSE("GPL");

module_init(memdev_init);
module_exit(memdev_exit);
