/* 信号量 */
/* 信号量也是等待，当一个进程使用了信号量，其它线程要使用先进入休眠 */
/* 伪代码 */

struct semaphore {
    spinlock_t      lockl;      //lock的自旋锁，保护count
    unsigned int    count;      //=0：此信号量正在被其他进程使用，现在不可以使用这个信号量，但是wait_list队列中没有进程在等待信号量
                                //<0：至少有一个进程在wait_list队列中等待信号量被释放
                                //>0：信号量空闲
    struct list_head wait_list; //等待队列，存放了睡眠的进程表
};

struct semaphore sema;

/* 初始化信号量，设置初始化值val */
static inline void sema_init(struct semaphore *sem, int val);
#define init_MUTEX(sema)    sema_init(sem,1)    //互斥量

#define init_MUTEX_LOCKED(sem) sem_init(sem, 0)

/* 获得信号量 */
void down(struct semaphore *sem)

/* 可被唤醒 */
int dowm_interruptible(struct semaphore *sem);
/* 如果信号量被唤醒会返回非零值 */
if (dowm_interruptible(&sem)) {
    return -ERESTARTSYS;
}

/* 当使用完信号量以后应该使用up()释放 */
void up(struct semaphore *sem);

/* 使用的模板 */
struct semaphore sem;
int xxx_init(void)
{
    //...
    init_MUTEX(&lock);
    //...
}

int xxx_open(struct inode *inode, struct file *filp)
{
    //...
    dowm(*sem); //不允许其他进程访问
    //...
    return 0;
}

int xxx_release(struct inode *inod, struct file *filp)
{
    //...
    up(&sem);
    //...
}