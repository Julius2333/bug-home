/* 完成量 */
/* 定义在include/linux/completion.h */

/* 结构体定义 */
struct completion{
    unsigned int done;
    wait_quenue_head_t wait;
};

/* 定义 */
struct inline void init_completion(struct completion *x)
{
    x->done = 0;
    init_waitqueue_head(&x->wait);
}

#define DECLARE_COMPLETION(work) \
    struct completion work = COMPLETION_IITIALIZER(work)

#define COMPLETION_INITIALIZER(work) \
    {0, __WAIT_QUEUE_HEAD_INITIALZER((work),wait)}

/* 等待完成量 */
void __sched wait_for_completion(struct completion *x)

/* 释放完成量 */
void complete(struct completion *x)
void complete_all(struct completion *x)





/* 使用完成量 */
struct completion com;
int xxx_completion(void)
{
    //...
    init_completion(&com);
    //...
}
int xxx_A()
{
    //...
    wait_for_completion(&com);
    //...
}

int xxx_B()
{
    //...
    complete(&com);
    //...
}
//...
