#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person
{
    char name[20];
    int age;
};

static int write_to_file(void)
{
    FILE *fp = NULL;
    struct person kim = {
        .name = "kim",
        .age = 20};
    struct person lee = {
        .name = "lee",
        .age = 30};

    if (!(fp = fopen("persons", "w")))
    {
        return -1;
    }

    if (fwrite(&kim, sizeof(struct person), 1, fp) != 1)
    {
        goto err;
    }
    if (fwrite(&lee, sizeof(struct person), 1, fp) != 1)
    {
        goto err;
    }

    fclose(fp);
    return 0;

err:
    if (fp)
    {
        fclose(fp);
    }
    return -1;
}

static int read_from_file(void)
{
    FILE *fp;
    int i;
    struct person persons[2];

    if (!(fp = fopen("persons", "r")))
    {
        return -1;
    }

    if (fread(persons, sizeof(struct person), 2, fp) != 2)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    for (i = 0; i < 2; i++)
    {
        printf("name: %s, age: %d\n",
               persons[i].name,
               persons[i].age);
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (write_to_file())
    {
        printf("write fail\n");
    }

    if (read_from_file())
    {
        printf("write fail\n");
    }

    return 0;
}

// bash `$ hexdump persons -C`
// 00000000  6b 69 6d 00 00 00 00 00  00 00 00 00 00 00 00 00  |kim.............|
// 00000010  00 00 00 00 14 00 00 00  6c 65 65 00 00 00 00 00  |........lee.....|
// 00000020  00 00 00 00 00 00 00 00  00 00 00 00 1e 00 00 00  |................|