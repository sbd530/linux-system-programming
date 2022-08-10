#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/procfs.h>

#define SHMKEY_FILEPATH "/tmp"
#define SHMKEY_PROJID 'r'
#define ROUNDUP(x) ((x) + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1)

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
    int n;
    key_t key;
    size_t size;
    int shmid;
    struct login_info local;
    struct login_info *info;

    /* get shared memory */
    key = ftok(SHMKEY_FILEPATH, SHMKEY_PROJID);
    if (key == -1)
    {
        perror("ftok()");
        return -1;
    }
    size = ROUNDUP(sizeof(struct login_info));
    shmid = shmget(key, size, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget()");
        return -1;
    }

    /* attach shared memory */
    info = shmat(shmid, NULL, 0);
    if (info == (void *)-1)
    {
        perror("shmat()");
        return -1;
    }
    memset(info, 0, sizeof(struct login_info));

    /* do monitoring */
    memset(&local, 0, sizeof(local));
    n = 0;
    while (1)
    {
        /* campare data on the memory */
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
    /* detach shared memory */
    shmdt(info);

    return 0;
}

static int do_login(void)
{
    key_t key;
    size_t size;
    int shmid;
    struct login_info *info;

    /* get shared memory */
    key = ftok(SHMKEY_FILEPATH, SHMKEY_PROJID);
    if (key == -1)
    {
        perror("ftok()");
        return -1;
    }
    size = ROUNDUP(sizeof(struct login_info));
    shmid = shmget(key, size, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget()");
        return -1;
    }

    /* attach shared memory */
    info = shmat(shmid, NULL, 0);
    if (info == (void *)-1)
    {
        perror("shmat()");
        return -1;
    }

    info->pid = getpid();
    info->counter++;

    shmdt(info);

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