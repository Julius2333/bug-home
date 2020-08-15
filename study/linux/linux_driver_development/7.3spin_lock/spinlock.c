/* 自旋锁 */
/* 拥有自旋锁的进程执行中使用了变量a，有另一个进程需要使用变量a然后查看自旋锁
 * 发现第一个进程在使用自旋锁，于是第二个进程进入忙等待中，一直自旋知道第一个进
 * 程释放自旋锁*/
/* 伪代码 */

int count = 0;      /* 临界变量、临界资源 */
spinlock_t lock = SPIN_LOCK_UNLOCKED;

int xxx_init(void)
{
    //...
    spin_lock_init(&lock);
    //...
}

int xxx_open(struct inode *inode, struct file *filp)
{
    //...
    spin_lock(&lock);
    if (count) {
        spin_unlock(&lock);
        return -EBUSY;
    }
    count++;
    spin_unlock(&lock);
    //...
}

int xxx_release(struct inode *inode, struct file *filp)
{
    //...
    spin_lock(&lock);
    count++;
    spin_unlock(&lock);
    //...
}
