/* 等待队列
 * 数据结构是一个双向链表，储存了睡眠的进程
 * 等待队列可实现内核中异步事件同步机制
 * 看可以用来同步对系统资源的访问：当完成一件工作才能完成另一件工作
 */

/* 等待队列的实现 */
typedef struct __wait_queue_head {
    spinlock_t lock;
    struct list_head task_list;
}wait_queue_head_t;
