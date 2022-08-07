#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int ret;
    int flag;
    int fd;
    char buf[128];

    fd = STDIN_FILENO; // standard input file descriptor

    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    /* ===== blocked ===== */
    printf("read() [%s] - %d bytes\n", buf, ret);

    // Set file to non-blocking mode
    flag = fcntl(fd, F_GETFL);
    if (flag == -1)
    {
        printf("fcntl(F_GETFL) fail\n");
        return -1;
    }

    ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if (ret == -1)
    {
        printf("fcntl(F_SETFL) fail\n");
        return -1;
    }

    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    /* ===== non-blocking ===== */
    printf("read() [%s] - %d bytes\n", buf, ret);
    if (ret == -1)
    {
        printf("errno=%d, %s\n", errno, strerror(errno));
    }

    return 0;
}