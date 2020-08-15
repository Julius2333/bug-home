/* 阻塞调用 */
/* 使用阻塞调用，当前线程会挂起必须一直等到子线程结束返回
 * 使用非阻塞调用，当前线程就会立即返回，那么就需要去查询
 */

/* select()非阻塞函数进行调用 */

void main()
{
    FLIE *fp;
    struct fd_set fds;
    struct timeval timeout = {4, 0};
    char buffer[256] = {0};
    fp = fopen{...};

    while (1) {
        FD_ZERO(&fds);
        FD_SET(fp, &fds);
        maxfdp = fp + 1;
        switch (select(maxfdp, &fds, &fds, NULL, &timeout)) {
            case -1:
                exit(-1);
                break;
            case 0:
                break;
            default:
                if (FD_ISSET(fp, &fds)) {
                    read(fds, buffer, 256, ...);
                    if (FD_ISSET(fp, &fds))
                        fwrite(fp, buffer, ...);
                }
        }
    }
}