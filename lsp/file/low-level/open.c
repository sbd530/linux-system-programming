#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
File open flags
  O_RDONLY : 읽기 전용
  O_WRONLY : 쓰기 전용
  O_RDWR : 읽기 & 쓰기
  O_CREAT : 파일이 존재하지 않으면 Regular file 생성
  O_NOFOLLOW : 파일이 Symbolic link인 경우 파일 열기 실패
  O_TRUNC : Regular file이 존재하는 경우 파일 사이즈를 0으로 만듬
  O_APPEND : Append mode로 열기(열자마자 파일 오프셋이 파일 끝에 위치함)
*/
static int write_file(void)
{
    int fd; // file descriptor
    /*
    int open(const char *pathname, int flags, mode_t mode);
    */
    fd = open("datafile", O_WRONLY | O_CREAT, 0600);
    printf("fd=%d\n", fd);
    if (fd == -1)
    {
        printf("open() error\n");
        return -1;
    }
    /*
    int dprintf(int fd, const char *format, ...);
    */
    dprintf(fd, "hello world %d\n", 123);
    close(fd);
    return 0;
}

static int trunc_file(void)
{
    int fd;
    /*
    int open(const char *pathname, int flags, mode_t mode);
    */
    fd = open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        printf("open() error\n");
        return -1;
    }
    /*
    int dprintf(int fd, const char *format, ...);
    */
    dprintf(fd, "Bye bye file \n");
    close(fd);
    return 0;
}

static int append_file(void)
{
    int fd;
    /*
    int open(const char *pathname, int flags);
    */
    fd = open("datafile", O_WRONLY | O_APPEND);
    if (fd == -1)
    {
        printf("open() error\n");
        return -1;
    }
    /*
    int dprintf(int fd, const char *format, ...);
    */
    dprintf(fd, "Hello again \n");
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    if (write_file())
    {
        printf("write_file() error\n");
    }
    if (trunc_file())
    {
        printf("trunc_file() error\n");
    }
    if (append_file())
    {
        printf("append_file() error\n");
    }
    return 0;
}