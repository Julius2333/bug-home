/* file operation struct */
/* 伪代码 */

static const struct file_operations xxx_fops = {
    .ower = THIS_MODLE,
    .read = xxx_read,
    .write = xxx_write,
    .ioctl = xxx_ioctl
};

static ssize_t xxx_read(  struct file *filp
                        , char _user *buf
                        , size_t size
                        , loff_t *ppos)
{
    //...
    if (size > 8) {
        copy_to_user(buf,...);  //large buf
    } else {
        put_user(...,buf);   //small buf
    }
    //...
}

static ssize_t xxx_write( struct file *filp
                        , const char _user *buf
                        , size_t size
                        , loff_t *ppos)
{
    //...
    if (size > 8) {
        copy _from_user(buf,...);
    } else {
        get_user(...,buf);
    }
    //...
}

static long xxx_ioctl(    struct file *filp
                        , unsigned int cmd
                        , unsigned long arg)
{
    //...
    switch (cmd) {
        case xxx_cmd1:
            //...
        break;
        case xxx_cmd2:
            //...
        break;
        default:
            return EINVAL;
    }
    return 0;
}