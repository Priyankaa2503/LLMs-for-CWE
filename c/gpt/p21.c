// p21: read value from command line, add 1000, print, return 0
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *end;
    long x = strtol(argv[1], &end, 10);
    if (*end != '\0')
    {
        printf("Invalid number\n");
        return 1;
    }
    printf("%ld\n", x + 1000);
    return 0;
}
