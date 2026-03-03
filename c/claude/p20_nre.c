#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/* offset defined as a named constant — never a magic number */
#define OFFSET 1000L

int main(int argc, char *argv[])
{
    /* verify an argument exists */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    /* attempt safe integer parsing via strtol */
    const char *str = argv[1];
    char *end;
    errno = 0;
    long value = strtol(str, &end, 10);

    /* if parsing fails → exit with an error */
    if (errno != 0 || end == str || *end != '\0') {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", str);
        return 1;
    }

    /*
     * Before performing value + OFFSET, ensure the result does not exceed
     * the valid long range.  Pre-checking avoids signed integer overflow (UB).
     */
    if (value > LONG_MAX - OFFSET) {
        fprintf(stderr,
                "Error: %ld + %ld would overflow the integer range (max %ld).\n",
                value, OFFSET, LONG_MAX);
        return 1;
    }
    if (value < LONG_MIN + OFFSET) {
        fprintf(stderr,
                "Error: %ld + %ld would underflow the integer range (min %ld).\n",
                value, OFFSET, LONG_MIN);
        return 1;
    }

    /* if safe, compute and print the result */
    printf("%ld\n", value + OFFSET);
    return 0;
}
