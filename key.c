/*
Module Author: Shamal Shaikh
CSE 3B
Project: Device Driver for changing LED config.
*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/string.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define KEY_STAT 0x60
#define KEY_DAT  0x64

u8 bit[7]={1,2,4,8,16,32,64};

#define SUCCESS 0
#define DEVICE_NAME "leds"           

int opendev(struct inode *i, struct file *f);
int closedev(struct inode *i, struct file *f);
ssize_t readme(struct file *f, char *c, size_t t, loff_t *o);
ssize_t writeme(struct file *f, const char *c, size_t t, loff_t *o);

static struct file_operations fops = {
  .read = readme, 
  .write = writeme,
  .open = opendev,
  .release = closedev
};

int atoi(const char * str, int lent)
{
    int res = 0,i=0; // Initialize result
  
    // Iterate through all characters of input string and
    // update result
    printk("buffer is : %s", str);
    for (i = 0; i<lent-1; ++i)
        res = res*10 + str[i] - '0';
  
    // return result.
    
    return res;
}


int Major;

static int hello_init(void)
{

	Major = register_chrdev(0, DEVICE_NAME, &fops);
		if(Major>0){
			printk("LEDS is Ready For Requests!: 	%d\n",Major);
			return 0;
		}else{
			printk("Something Bad happened OhOhhh: %d",Major); return -1;
		}
	
	printk(KERN_ALERT "hello world \n");
	u8 val_stat,val_data;
//	int timeout = 3000;
	val_stat = inb(KEY_STAT);
//	val_data = inb(KEY_DAT);
	outb(0xed,0x60);
//	udelay(timeout);

	printk(KERN_ALERT "%d %d\n",val_stat,val_data);

		//val_stat|=bit[2];
		// val_stat|=bit[2];
		// //val_stat|=bit[0];
		// outb(val_stat,KEY_STAT);
 	printk(KERN_ALERT "%d %d\n",val_stat,val_data);
	return 0;
}


static void hello_exit(void)
{
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_ALERT " good bye \n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

int opendev(struct inode * a, struct file * b)
{
  printk("Someone opened me!\n");
  //nothing to do!!!
  return SUCCESS;
}
int closedev(struct inode * a, struct file * b)
{
  //nothing to do!!
  printk("Someone Closed me!\n");
  return SUCCESS;
}

ssize_t readme(struct file *filp,char *buffer,size_t length,loff_t *offset)  
{
    //  int len;
    //  struct timeval time;
    //  do_gettimeofday(&time);
    // // char *b=NULL;
    //  b=kmalloc(sizeof(char)*40,GFP_KERNEL);
    //  len=itoa(time.tv_sec,b);
    //  copy_to_user(buffer,b,len);
    //  printk("Return val:%s\n",b);
    //  return length;  
    return 0;
}

ssize_t writeme(struct file *filp,const char *buff,size_t len, loff_t *off)
{
  int i=atoi(buff, len);
  printk("length of buffer : %d", len);

  u8 val_stat;
  printk("hello input = %d",i);
  switch(i){
  	case 1:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[0];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 2:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[1];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 3:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[2];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 12:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[0];
  	val_stat|=bit[1];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 23:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[1];
  	val_stat|=bit[2];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 13:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[0];
  	val_stat|=bit[2];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}
  	case 123:{
  		val_stat = inb(KEY_STAT);
  	val_stat|=bit[0];
  	val_stat|=bit[1];
  	val_stat|=bit[2];
  	outb(0xed,0x60);
  	outb(val_stat,KEY_STAT);
  	break;
  	}

  }
  
  return len;
  
}

MODULE_AUTHOR("SHAMAL");
/*
 cat /proc/ioports
 cat /proc/iomem
*/
