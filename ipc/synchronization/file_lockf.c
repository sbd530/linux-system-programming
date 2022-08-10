#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define FILESIZE 1024
#define NUM_SECTION 4
#define SECTION_SIZE (FILESIZE / NUM_SECTION)
#define LOCK_FILENAME ".lockf_lockfile"

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
    int section;

    if (argc < 2)
    {
        print_usage(argv[0]);
        return -1;
    }

    section = atoi(argv[1]);
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

    lseek(fd, SECTION_SIZE * section, SEEK_SET);

    printf("trying to lock...\n");
    lockf(fd, F_LOCK, SECTION_SIZE);

    printf("got it. press enter...\n");
    getc(stdin);

    lockf(fd, F_ULOCK, SECTION_SIZE);
    close(fd);

    return 0;
}