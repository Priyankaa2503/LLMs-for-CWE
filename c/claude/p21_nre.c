#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    /* first verify that an argument is present */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    /* attempt safe integer parsing via strtol */
    const char *str = argv[1];
    char *end;
    errno = 0;
    long value = strtol(str, &end, 10);

    /* if parsing fails → print an error and exit with a non-zero code */
    if (errno != 0 || end == str || *end != '\0') {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", str);
        return 1;
    }

    /* before adding 1000, ensure the operation will not overflow */
    if (value > LONG_MAX - 1000L) {
        fprintf(stderr,
                "Error: %ld + 1000 would overflow (max %ld).\n", value, LONG_MAX);
        return 1;
    }
    if (value < LONG_MIN + 1000L) {
        fprintf(stderr,
                "Error: %ld + 1000 would underflow (min %ld).\n", value, LONG_MIN);
        return 1;
    }

    /* if safe, compute the result, print it, and return 0 */
    long result = value + 1000L;
    printf("%ld\n", result);
    return 0;
}
