#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>                 //kmalloc()
#include <linux/uaccess.h>              //copy_to/from_user()
#include <linux/kobject.h> 

#define memory_size        1024           //Memory Size

dev_t dev = 0;
static struct class *dev_class;
static struct cdev character_driver_cdev;
struct kobject *kobj_ref;
uint8_t *kernel_buffer;

/*
** Function Prototypes
*/
static int      __init character_driver_init(void);
static void     __exit character_driver_exit(void);
 
/*************** Driver functions **********************/
static int      character_driver_open(struct inode *inode, struct file *file);
static int      character_driver_release(struct inode *inode, struct file *file);
static ssize_t  character_driver_read(struct file *filp, 
                        char __user *buf, size_t len,loff_t * off);
static ssize_t  character_driver_write(struct file *filp, 
                        const char *buf, size_t len, loff_t * off);
 
/*
** File operation sturcture
*/
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = character_driver_read,
        .write          = character_driver_write,
        .open           = character_driver_open,
        .release        = character_driver_release,
};

/**@brief This function will be called when we open the Device file.  
 */
static int character_driver_open(struct inode *inode, struct file *file)
{
        /*Creating Physical memory*/
        if((kernel_buffer = kmalloc(memory_size , GFP_KERNEL)) == 0){
            pr_info("Cannot allocate memory in kernel\n");
            return -1;
        }
        pr_info("Device File Opened...!!!\n");
        return 0;
}

/**@brief This function will be called when we close the Device file
*/ 
static int character_driver_release(struct inode *inode, struct file *file)
{
        kfree(kernel_buffer);
        pr_info("Device File Closed...!!!\n");
        return 0;
}
 

/**@brief This function will be called when we read the Device file
*/
static ssize_t character_driver_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
	//Copy the data from the kernel space to the user-space
        if( copy_to_user(buf, kernel_buffer, memory_size) )
        {
                pr_err("Data Read : Err!\n");
        }
        pr_info("Read function\n");

        return memory_size;
}

/**@brief This function will be called when we write the Device file
*/
static ssize_t character_driver_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
	//Copy the data to kernel space from the user-space
        if( copy_from_user(kernel_buffer, buf, len) )
        {
                pr_err("Data Write : Err!\n");
        }
        pr_info("Write Function\n");
    
        return len;
}
 

/**@brief Module Init function
*/
static int __init character_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "character_driver_Dev")) <0){
                pr_info("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&character_driver_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&character_driver_cdev,dev,1)) < 0){
            pr_info("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"character_driver_class")) == NULL){
            pr_info("Cannot create the struct class\n");
            goto r_class;
        }

        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"character_driver_device")) == NULL){
            pr_info("Cannot create the Device 1\n");
            goto r_device;
        }
        
        /*Creating Physical memory*/
        if((kernel_buffer = kmalloc(memory_size , GFP_KERNEL)) == 0){
            pr_info("Cannot allocate memory in kernel\n");
            goto r_device;
        }
        
        strcpy(kernel_buffer, "Hello");


        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&character_driver_cdev);
        return -1;
}

/**@brief Module exit function
*/
static void __exit character_driver_exit(void)
{
	kfree(kernel_buffer);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&character_driver_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}
 
module_init(character_driver_init);
module_exit(character_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("author's name");
MODULE_DESCRIPTION("Simple Linux device driver");
MODULE_VERSION("1.8");
