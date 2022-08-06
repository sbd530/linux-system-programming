#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
/*
struct dirent {
    ino_t          d_ino;       Inode number
    off_t          d_off;       Not an offset; see below
    unsigned short d_reclen;    Length of this record
    unsigned char  d_type;      Type of file; not supported
                                 by all filesystem types
    char           d_name[256]; Null-terminated filename
};
*/

#define TYPE2STR(X)                    \
    ((X) == DT_BLK    ? "block device" \
     : (X) == DT_CHR  ? "char device"  \
     : (X) == DT_DIR  ? "directory"    \
     : (X) == DT_FIFO ? "fifo"         \
     : (X) == DT_LNK  ? "symlink"      \
     : (X) == DT_REG  ? "regular file" \
     : (X) == DT_SOCK ? "socket"       \
                      : "unknown")

int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *entry;
    /*
    #include <sys/types.h>
    #include <dirent.h>
    DIR *opendir(const char *name);
    */
    dp = opendir("."); // 현재 디렉터리
    if (!dp)
    {
        printf("opendir() fail\n");
        return -1;
    }

    /*
    struct dirent *readdir(DIR *dirp);
    */
    while ((entry = readdir(dp)))
    {
        printf("%s: %s\n", entry->d_name, TYPE2STR(entry->d_type));
    }

    /*
    int closedir(DIR *dirp);
    */
    closedir(dp);
    return 0;
}