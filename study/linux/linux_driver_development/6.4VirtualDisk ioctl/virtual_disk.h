/* virtual disk的头文件宏和设备结构体 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define VIRTUALDISK_SIZE    0x2000  /* 全局最大8k字节 */
#define MEM_CLEAR 0x1               /* 全局内存清零 */
#define PORT1_SET 0x2               /* 将port1端口清零 */
#define PORT2_SET 0x3               /* 将port1端口清零 */
#define VIRTUALDISK_MAJOR   200     /* 预设的VirtualDisk的主设备号为200 */

/* VirtualDisk设备结构体 */
struct VirtualDisk {
    struct cdev cdev;                       /* cdev结构体 */
    unsigned char mem[VIRTUALDISK_SIZE];    /* 全局内存8K */
    int port1;                              /* 两个不同类型的端口 */
    long port2;
    long count;                             /* 记录设备目前被多少设备打开 */
}
