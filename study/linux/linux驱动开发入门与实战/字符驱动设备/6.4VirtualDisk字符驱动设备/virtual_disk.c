#include "virtual_disk.h"

static int VirtualDisk_major = VIRTUALDISK_MAJOR;

int VirtualDisk_open(struct inode *inode, struct file *filp)
{
    /* 将设备结构体指针赋值给文件私有数据指针 */
    filp->private_data = Virtualdisk_devp;
    struct VirtualDisk *devp = filp->private_data;
    devp->count++;      /* 每当有一个app打开设备加一 */
    return 0;
}

int VirtualDisk_release(struct inode *inode, struct file *filp)
{
    struct VirtualDisk *devp = filp->private_data;
    devp->count--;
    return 0;
}

static ssize_t VirtualDisk_read(  struct file *filp
                                , char __user *buf
                                , size_t size
                                , loff_t *ppos)
{
    unsigned long p = *ppos;    /* 记录文件指针偏移位置 */
    unsigned int count = size;  /* 记录需要读取的字节数 */
    int ret = 0;
    struct VirtualDisk *devp = file->private_data;  /* 获得设备结构体指针 */

    /* 输入参数检查，读取的地址与偏移不嫩超过最大设备空间 */
    if (p >= VIRTUALDISK_SIZE) {
        return count ? -ENXIO : 0;
    }
    if (count > VIRTUALDISK_SIZE) {
        count = VIRTUALDISK_SIZE - p;
    }

    /* 内核发送到用户空间 */
    if (copy_to_user(buf, (void*)(devp->mem + p), count)) {
        ret = -EFAULT;
    } else {
        *ppos += count;
        ret = count;
        printk(KERN_INFO "read %d bytes(s) from %d\n", count, p);
    }
    return ret;
}

static ssize_t VirtualDisk_write( struct file *filp
                                , const char __user *buf
                                , size_t size
                                , loff_t *ppos)
{
    undigned long p = *ppop;
    int ret = 0;
    undigned int count = size;
    struct VirtualDisk *devp = file->private_data;

    /* 输入参数检查，写入的地址与偏移不嫩超过最大设备空间 */
    if (p >= VIRTUALDISK_SIZE) {
        return count ? -ENXIO : 0;
    }
    if (count > VIRTUDISK_SIZE) {
        count = VIRTUALDISK_SIZE - p;
    }

    /* 用户空间发送给内核 */
    if (copy_from_user(devp->mem + p, buf, count)) {
        ret = -EFAULT;
    } else {
        *ppos += count; /* 增加偏移位置 */
        ret = count;
        printk(KERN_INHO "written %d bytes(s) from %d\n", count, p);
    }
    return ret;
}

/* seek文件定位函数 */
static loff_t VirtualDisk_llseek( struct file *filp
                                , loff_t offset
                                , int orig)
{
    loff_t ret = 0;
    switch (orig) {
        case SEEK_SET:  /* 相对文件开始位置的偏移 */
            if (offset < 0) {
                ret = -EINVAL;
                break;
            }
            if ((unsigned int)offset > VIRTUALDISK_SIZE) {
                ret = -EINVAL;
                break;
            }
            filp->f_pos = (unsigned int)offset;     /* 更新文件指针位置 */
            ret = filp->pos;
            break;
        case SEEK_CUR:  /* 相对文件当前位置的偏移 */
            if ((filp->f_pos + offset) > VIRTUALDISK_SIZE) {
                ret = -EINVAL;
                break;
            }
            if ((filp->f_pos + offset) < 0) {
                ret = -EINVAL;
                break;
            }
            filp->f_pos += offset;
            ret = filp->f_pos;
            break;
        default:
            ret = -EINVAL;
            break;
    }
    return ret;
}

static int VirtualDisk_ioctl( struct inode *inodep
                            , struct file *filp
                            , unsigned int cmd
                            , unsigned long arg)
{
    struct VirtualDisk *devp = filp->private_data;

    switch (cmd)    /* 支持3个命令 */
    {
        case MEM_CLEAR:
            memset(devp->mem, 0, VIRTUALDISK_SIZE);
            printk(KERN_INFO "VirtualDisk is set to zero\n");
            break;
        case PORT1_SET:
            devp->port1 = 0;
            break;
        case PORT2_SET:
            devp->port2 = 0;
            break;
        default:
            return -EINVAL;
            break;
    }
    return 0;
}

/* 文件操作结构体 */
static const struct file_operations VirtualDisk_fops = {
    .owner = THIS_MODULE,
    .llseek = VirtualDisk_llseek,       /* 定位偏移量函数 */
    .read = VirtualDisk_read,
    .write = VirtualDisk_write,
    .ioctl = VirtualDisk_ioctl,
    .open = VirtualDisk_open,
    .release = VirtualDisk_release,     /* 释放设备函数 */
}

/* 初始化并且注册cdev */
static void VirtualDisk_setup_cdev(struct VirtualDisk *dev, int minor)
{
    int ret;

    devno = MKDEV(VirtualDisk_major, minor);    /* 构造设备号 */
    cdev_init(&dev->cdev, &VirtualDisk_fops);   /* 初始化cdev设备 */
    dev->cdev.owner = THIS_MODULE;              /* 使构造的驱动程序属于该模块 */
    dev->cdev.ops = &VirtualDisk_fops;          /* cdev连接file_operations */
    ret = cdev_add(&dev->cdev, devno, 1);       /* 将cdev注册系统中 */
    if (ret) {
        printk(KERN_NOTICE "Error in cdev_add()\n");
    }
}

int VirtualDisk_init(void)
{
    int result;

    /* 构建设备号 */
    dev_t devno = MKDEV(VirtualDisk_major, 0);

    /* 申请设备号 */
    if (VirtualDisk_major) {
        result = register_chrdev_region(devno, 1, "VirtualDisk");   //静态申请
    } else {
        result = alloc_chrdev_region(&devno, 0, 1, "VirtualDisk");  //动态申请
        VitrualDisk_major = MAJOR(devno);
    }
    if (result < 0) {
        return result;
    }

    /* 动态申请设备结构体的内存 */
    Virtualdisk_devp = kmalloc(sizeof(struct VirtualDisk), GFP_KERNEL);
    if (Virtualdisk_devp == NULL) {
        result = -ENOMEM;
        goto fail_kmalloc;
    }
    memset(Virtualdisk, 0, sizeof(struct VirtualDisk));

    /* 初始化并且添加cdev结构体 */
    VirtualDisk_setup_cdev(Virtualdisk_devo, 0);
    return 0;

fail_kmalloc:
    unregister_chrdev_region(devno, 1);
    return result;
}

void VirtualDisk_exit(void)
{
    cdev_del(&Virtualdisk_devp->cdev);      //注销cdev
    kfree(Virtualdisk_devp);                //释放设备内存
    unregister_chdev_region(MKDEV(VirtualDisk_major, 0), 1);    //释放设备号
}




