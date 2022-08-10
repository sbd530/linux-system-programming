#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>

#define FLOCK_FILENAME ".flock_test"

static void print_usage(const char *progname)
{
    printf("%s (sh|ex)\n", progname);
}

int main(int argc, char **argv)
{
    int ops;
    int fd;

    if (argc < 2)
    {
        print_usage(argv[0]);
        return -1;
    }

    if (!strcmp(argv[1], "sh"))
    {
        ops = LOCK_SH;
    }
    else if (!strcmp(argv[1], "ex"))
    {
        ops = LOCK_EX;
    }
    else if (!strcmp(argv[1], "un"))
    {
        ops = LOCK_UN;
    }
    else
    {
        print_usage(argv[0]);
        return -1;
    }

    fd = open(FLOCK_FILENAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open()");
        return -1;
    }

    /* lock */
    printf("trying to grab the lock\n");
    flock(fd, ops);

    printf("got it. waiting for enter...\n");
    /* wait */
    getc(stdin);

    /* unlock */
    flock(fd, LOCK_UN);

    close(fd);
    return 0;
}
