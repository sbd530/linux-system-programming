#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
#define TARGET_FILE "hello_world"
    /*
    Hard link
        #include <unistd.h>
        int link(const char *oldpath, const char *newpath);
    */
    if (link(TARGET_FILE, "hello_by_link"))
    {
        printf("link() fail\n");
        return -1;
    }
    /*
    Symbolic link
        #include <unistd.h>
        int symlink(const char *target, const char *linkpath);
    */
    if (symlink(TARGET_FILE, "hello_by_symlink"))
    {
        printf("symlink() fail\n");
        return -1;
    }
    return 0;
}