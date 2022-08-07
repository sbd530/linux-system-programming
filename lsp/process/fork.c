#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test_func(void)
{
    printf("this is a tets function(pid %d)\n", getpid());
}

int main(int argc, char **argv)
{
    /*
    #include <sys/types.h>
    #include <unistd.h>
    pid_t fork(void);
    */
    pid_t pid;

    printf("origin process pid: %d\n", getpid());

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        printf("child process pid: %d\n", getpid());
    }
    else if (pid > 0)
    {
        /* Parent process */
        printf("parent process pid: %d, child pid: %d\n", getpid(), pid);
    }

    test_func();

    return 0;
}