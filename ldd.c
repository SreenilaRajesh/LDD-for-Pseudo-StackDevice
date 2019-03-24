 #include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>/* for char dev support*/
#include<linux/uaccess.h>
static int Device_Open = 0;
static int count=-1;
char b[8][20];
int r;
int open(struct inode *pin,struct file *p)
{
    if(Device_Open)
    return -EBUSY;

    Device_Open++;
    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    return 0;
}
ssize_t read(struct file *p, char __user *buffer, size_t size, loff_t *offset)//len is the length of the buffer
{
    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    if(count<0)
    return -EFAULT;
    r = copy_to_user(buffer,b[count],size);
     count--;
//   return size;
    return r;
}
ssize_t write(struct file *p, const char __user *buffer, size_t size, loff_t *offset)
{


    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    if(count>=7)
    return -EFAULT;
    b[count+1][0]='\0';
    r = copy_from_user(b[++count], buffer, size);
    return r;
}
int close(struct inode *pin, struct file *p)//function associated with close fd command
{
    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    Device_Open--;
    return 0;
}
/* define a structure to hold the file operations done on this device*/
/* this structure is defined in the header fs.h */

struct file_operations fop = {
    .owner = THIS_MODULE,
    .open = open,
    .read = read,
    .write = write,
    .release = close
};/*initializing the fields*/
int dinit(void)
{
    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    /*register with the kernel and indicate it*/
    register_chrdev(265/*major number*/,"SDD"/*name of the driver*/,&fop/* it is a ptr to the file operations*/);
    return 0;
}
void dexit(void)
{
    printk(KERN_ALERT "Function %s \n",__FUNCTION__);
    /*unregister the driver*/
    unregister_chrdev(265/*major number of the device(same as given before)*/,"SDD"/*name of the driver*/);
}
module_init(dinit);
module_exit(dexit);/* the macros...*/
