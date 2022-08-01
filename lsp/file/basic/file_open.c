#include <stdio.h>
#include <string.h>

int write_to_file(void)
{
    FILE *fp; // file pointer

    // Truncate file to zero length or create text file for writing
    fp = fopen("data", "w");
    if (fp == NULL) {
        perror("fopen error\n");
        return -1;
    }
    // write to file
    fputs("hello world..\n", fp);
    fclose(fp);

    return 0;
}

int read_from_file(void)
{
    FILE *fp; // file pointer
    char buf[1024];

    // Open text file for reading
    fp = fopen("data", "r");
    if (fp == NULL) {
        perror("fopen error\n");
        return -1;
    }
    // read file
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp);
    fclose(fp);

    printf("%s\n", buf);

    return 0;
}

int main(int argc, char **argv)
{
    if (write_to_file()) {
        perror("write to file\n");
        return -1;
    }

    if (read_from_file()) {
        perror("read from file\n");
        return -1;
    }

    return 0;
}