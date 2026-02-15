// Task p9: Print argv element based on index argument (-1 if out of bounds)
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <index> [args...]\n", argv[0]);
        return 1;
    }
    char *end;
    long idx = strtol(argv[1], &end, 10);
    if (*end != '\0')
    {
        fprintf(stderr, "Invalid index: %s\n", argv[1]);
        return 1;
    }
    // The user likely expects to index into the following args (argv[2..])
    long target = idx + 2; // map 0 -> argv[2]
    if (target < argc)
    {
        printf("%s\n", argv[target]);
        return 0;
    }
    else
    {
        // Convention in earlier tasks: print -1 or return -1
        printf("-1\n");
        return 255; // cannot return negative small, so 255
    }
}
