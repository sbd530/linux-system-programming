#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHARED_FILENAME "shared"

struct login_info
{
    int pid;
    int counter;
};

static void print_usage(const char *progname)
{
    printf("%s (monitor)\n", progname);
}

static int do_monitoring(void)
{
    int fd;
    int n;
    struct login_info local;
    struct login_info *info;

    fd = open(SHARED_FILENAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open()");
        return -1;
    }

    if (ftruncate(fd, sizeof(struct login_info)))
    {
        perror("ftruncate()");
        close(fd);
        return -1;
    }

    info = mmap(NULL, sizeof(struct login_info),
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (info == MAP_FAILED)
    {
        perror("mmap()");
        close(fd);
        return -1;
    }
    memset(info, 0, sizeof(struct login_info));

    close(fd);

    memset(&local, 0, sizeof(local));
    n = 0;
    while (1)
    {
        if (memcmp(info, &local, sizeof(struct login_info)))
        {
            /* diff */
            printf("pid = %d, counter = %d\n", info->pid, info->counter);
            memcpy(&local, info, sizeof(struct login_info));
            n++;

            if (n == 5)
                break;
        }
        sleep(1);
    }
    munmap(info, sizeof(struct login_info));

    return 0;
}

static int do_login(void)
{
    int fd;
    struct login_info *info;

    fd = open(SHARED_FILENAME, O_RDWR);
    if (fd == -1)
    {
        perror("open()");
        return -1;
    }

    info = mmap(NULL, sizeof(struct login_info),
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (info == MAP_FAILED)
    {
        perror("mmap()");
        close(fd);
        return -1;
    }

    close(fd);

    info->pid = getpid();
    info->counter++;

    munmap(info, sizeof(struct login_info));

    return 0;
}

int main(int argc, char **argv)
{
    int monitor = 0;

    if (argc == 2)
    {
        if (!strcmp(argv[1], "monitor"))
        {
            monitor = 1;
        }
        else
        {
            print_usage(argv[0]);
            return -1;
        }
    }
    else if (argc > 2)
    {
        print_usage(argv[0]);
        return -1;
    }

    if (monitor)
    {
        do_monitoring();
    }
    else
    {
        do_login();
    }
    return 0;
}