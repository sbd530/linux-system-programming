#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

struct login_info
{
    int pid;
    int counter;
};

struct login_info *login_info_init(void)
{
    struct login_info *info;

    info = mmap(NULL, sizeof(struct login_info),
                PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
                -1, 0);
    if (info == MAP_FAILED)
    {
        perror("mmap()");
        return NULL;
    }
    memset(info, 0, sizeof(struct login_info));

    return info;
}

static int do_monitoring(struct login_info *info)
{
    int n;
    struct login_info local;

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
        usleep(100000);
    }

    return 0;
}

static int do_login(int index, struct login_info *info)
{
    sleep(index + 1);

    info->pid = getpid();
    info->counter++;

    return 0;
}

int main(int argc, char **argv)
{
    int i;
    int pid;
    struct login_info *info;

    info = login_info_init();
    if (!info)
    {
        perror("login_info_init()");
        return -1;
    }

#define NUM_FORK 5
    for (i = 0; i < NUM_FORK; ++i)
    {
        pid = fork();
        if (pid > 0)
        {
        }
        else if (pid == 0)
        {
            /* child */
            do_login(i, info);
            munmap(info, sizeof(struct login_info));
            return 0;
        }
        else
        {
            /* error */
            perror("fork()");
            return -1;
        }
    }
    /* parent */
    do_monitoring(info);
    for (i = 0; i < NUM_FORK; ++i)
    {
        pid = wait(NULL);
        printf("pid %d is end\n", pid);
    }

    return 0;
}