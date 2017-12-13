/*************************************************************************
	> File Name: hellomodule.c
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Tue 24 Oct 2017 05:01:33 AM PDT
 ************************************************************************/
#include <linux/init.h>
#include <linux/module.h>

static int hello_init()
{
    printk(KERN_WARNING"Hello world!\n");
    return 0;
}
static void hello_exit()
{
    printk(KERN_WARNING"hello exit\n");
}
module_init(hello_init);
module_exit(hello_exit);

