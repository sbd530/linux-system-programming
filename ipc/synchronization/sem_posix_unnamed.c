#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/test"

struct login_info
{
    sem_t sem;
    int pid;
    int counter;
};

static void print_usage(const char *progname)
{
    printf("%s (monitor|get|put)\n", progname);
}

static int do_monitoring(void)
{
    int fd;
    int n;
    int val;
    struct login_info local;
    struct login_info *info;

    fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("shm_open()");
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

    /* init sem */
    /* 1 : inter process */
    if (sem_init(&info->sem, 1, 3) == -1)
    {
        perror("sem_init()");
        close(fd);
        return -1;
    }

    close(fd);

    memset(&local, 0, sizeof(local));
    n = 0;
    while (1)
    {
        if (memcmp(info, &local, sizeof(struct login_info)))
        {
            /* diff */
            sem_getvalue(&info->sem, &val);
            printf("pid = %d, counter = %d, sem = %d\n", info->pid, info->counter, val);
            memcpy(&local, info, sizeof(struct login_info));
            n++;

            if (n == 15)
                break;
        }
        sleep(1);
    }
    sem_destroy(&info->sem);
    munmap(info, sizeof(struct login_info));

    return 0;
}

static int do_login(void)
{
    int fd;
    struct login_info *info;

    printf("pid = %d\n", getpid());

    fd = shm_open(SHM_NAME, O_RDWR, 0644);
    if (fd == -1)
    {
        perror("shm_open()");
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

    /* get sem */
    sem_wait(&info->sem);
    /* critical section ####################*/
    info->pid = getpid();
    info->counter++;
    /*######################################*/

    munmap(info, sizeof(struct login_info));

    return 0;
}

static int do_logout(void)
{
    int fd;
    struct login_info *info;

    fd = shm_open(SHM_NAME, O_RDWR, 0644);
    if (fd == -1)
    {
        perror("shm_open()");
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

    /* put sem */
    sem_post(&info->sem);

    munmap(info, sizeof(struct login_info));

    return 0;
}

int main(int argc, char **argv)
{
    int monitor = 0;
    int get;

    if (argc == 2)
    {
        if (!strcmp(argv[1], "monitor"))
        {
            monitor = 1;
        }
        else if (!strcmp(argv[1], "get"))
        {
            get = 1;
        }
        else if (!strcmp(argv[1], "put"))
        {
            get = 0;
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
        if (get)
        {
            do_login();
        }
        else
        {
            do_logout();
        }
    }
    return 0;
}