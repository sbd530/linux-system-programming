#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define FTOK_PATH "/tmp"
#define FTOK_PROJ_ID 'd'
#define NUM_SEM 2

static void print_usage(char *progname)
{
    printf("%s (init|get SEM_INDEX|release SEM_INDEX|show|wait0 SEM_INDEX)\n",
           progname);
}

static int init_semaphore(void)
{
    key_t key;
    int semid;

    key = ftok(FTOK_PATH, FTOK_PROJ_ID);
    if (key == -1)
    {
        perror("ftok()");
        return -1;
    }
    /* int semget(key_t key, int nsems, int semflg); */
    semid = semget(key, NUM_SEM, IPC_CREAT | 0644);
    if (semid == -1)
    {
        perror("semget()");
        return -1;
    }
    return semid;
}

static int sem_sysv_init(int sem_id)
{
    semctl(sem_id, 0, SETVAL, 1); /* binary semaphore */
    semctl(sem_id, 1, SETVAL, 3); /* counting semaphore */

    return 0;
}

static int sem_sysv_show(int sem_id)
{
    int i;

    for (i = 0; i < NUM_SEM; ++i)
    {
        printf("semaphore[%d] = %d\n", i, semctl(sem_id, i, GETVAL));
    }
    return 0;
}

static int sem_sysv_get(int sem_id, int sem_idx)
{
    struct sembuf buf;

    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = -1;
    semop(sem_id, &buf, 1);
    return 0;
}

static int sem_sysv_release(int sem_id, int sem_idx)
{
    struct sembuf buf;

    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = 1;
    semop(sem_id, &buf, 1);
    return 0;
}

static int sem_sysv_wait0(int sem_id, int sem_idx)
{
    struct sembuf buf;

    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = -1;
    semop(sem_id, &buf, 0);
    return 0;
}

int main(int argc, char **argv)
{
    int sem_id;
    int sem_idx;
    int ret;

    if (argc < 2)
    {
        print_usage(argv[0]);
        return -1;
    }

    sem_id = init_semaphore();
    if (sem_id == -1)
    {
        perror("init_semaphore()");
        return -1;
    }

    if (!strcmp(argv[1], "init"))
    {
        ret = sem_sysv_init(sem_id);
    }
    else if (!strcmp(argv[1], "show"))
    {
        ret = sem_sysv_show(sem_id);
    }
    else if (!strcmp(argv[1], "get"))
    {
        if (argc < 3)
        {
            print_usage(argv[0]);
            return -1;
        }
        sem_idx = atoi(argv[2]);
        ret = sem_sysv_get(sem_id, sem_idx);
    }
    else if (!strcmp(argv[1], "release"))
    {
        if (argc < 3)
        {
            print_usage(argv[0]);
            return -1;
        }
        sem_idx = atoi(argv[2]);
        ret = sem_sysv_release(sem_id, sem_idx);
    }
    else if (!strcmp(argv[1], "wait0"))
    {
        if (argc < 3)
        {
            print_usage(argv[0]);
            return -1;
        }
        sem_idx = atoi(argv[2]);
        ret = sem_sysv_wait0(sem_id, sem_idx);
    }
    else
    {
        print_usage(argv[0]);
        return -1;
    }
    return ret;
}