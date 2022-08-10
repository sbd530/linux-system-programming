/*
하나의 파일에 대해 구역을 나눠서 락을 지정한다.
구역만 다르면 여러 프로세스가 동시에 하나의 파일에 접근할 수 있다.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define FILESIZE 1024
#define NUM_SECTION 4
#define LOCK_FILENAME ".fcntl_lockfile"

static int open_file(void)
{
    int fd;

    fd = open(LOCK_FILENAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open()");
        return -1;
    }

    if (ftruncate(fd, FILESIZE) == -1)
    {
        perror("ftruncate()");
        return -1;
    }

    return fd;
}

static void print_usage(const char *progname)
{
    printf("%s (rd|wr) #SECTION\n", progname);
}

int main(int argc, char **argv)
{
    int fd;
    struct flock fl;
    int section;

    if (argc < 2)
    {
        print_usage(argv[0]);
        return -1;
    }

    memset(&fl, 0, sizeof(fl));
    if (!strcmp(argv[1], "rd"))
    {
        fl.l_type = F_RDLCK;
    }
    else if (!strcmp(argv[1], "wr"))
    {
        fl.l_type = F_WRLCK;
    }
    else
    {
        perror("open_file()");
        return -1;
    }

    section = atoi(argv[2]);
    if (section >= NUM_SECTION)
    {
        print_usage(argv[0]);
        return -1;
    }

    fd = open_file();
    if (fd == -1)
    {
        perror("open_file()");
        return -1;
    }

#if 0
struct flock {
    ...
    short l_type;    /* Type of lock: F_RDLCK,
                        F_WRLCK, F_UNLCK */
    short l_whence;  /* How to interpret l_start:
                        SEEK_SET, SEEK_CUR, SEEK_END */
    off_t l_start;   /* Starting offset for lock */
    off_t l_len;     /* Number of bytes to lock */
    pid_t l_pid;     /* PID of process blocking our lock
                        (set by F_GETLK and F_OFD_GETLK) */
    ...
};
#endif
    fl.l_whence = SEEK_SET;
    fl.l_start = (FILESIZE / NUM_SECTION) * section;
    fl.l_len = (FILESIZE / NUM_SECTION);
    /* get lock */
    printf("trying to lock...\n");
    fcntl(fd, F_SETLKW, &fl);

    printf("got it. press enter...\n");
    getc(stdin);

    /* unlock */
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);

    close(fd);
    return 0;
}