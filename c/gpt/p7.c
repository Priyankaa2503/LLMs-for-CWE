// Task p7: atoi-like conversion of argv[1] and print argv[INDEX]
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s INDEX [args...]\n", argv[0]);
        return 0;
    }

    int idx = atoi(argv[1]);
    if (idx >= 0 && idx < argc)
    {
        printf("%s\n", argv[idx]);
    }
    else
    {
        printf("\n");
    }

    return 0;
}
