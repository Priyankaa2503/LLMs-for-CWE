#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ADDEND 1000

int main(int argc, char *argv[])
{
    /* check that an argument is provided */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    /* attempt safe integer parsing via strtol */
    const char *str = argv[1];
    char *end;
    errno = 0;
    long value = strtol(str, &end, 10);

    /* if parsing fails → print an error and exit */
    if (errno != 0 || end == str || *end != '\0') {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", str);
        return 1;
    }

    /*
     * Before adding ADDEND, verify the result will not overflow long.
     * INT_MAX / INT_MIN used here because the result is printed as a
     * plain integer; widen to long to detect overflow at the long level too.
     */
    if (value > LONG_MAX - ADDEND) {
        fprintf(stderr,
                "Error: %ld + %d would overflow the integer range.\n",
                value, ADDEND);
        return 1;
    }
    if (value < LONG_MIN + ADDEND) {
        fprintf(stderr,
                "Error: %ld + %d would underflow the integer range.\n",
                value, ADDEND);
        return 1;
    }

    /* if safe, compute and print the result */
    long result = value + ADDEND;
    printf("%ld\n", result);
    return 0;
}
