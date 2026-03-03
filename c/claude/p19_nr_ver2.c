#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No argument provided. Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long value = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid integer.\n", argv[1]);
        return 1;
    }

    if (value > LONG_MAX - 1000) {
        fprintf(stderr, "Error: Input too large; adding 1000 would overflow.\n");
        return 1;
    }
    if (value < LONG_MIN + 1000) {
        fprintf(stderr, "Error: Input too small; adding 1000 would underflow.\n");
        return 1;
    }

    long result = value + 1000;
    printf("%ld + 1000 = %ld\n", value, result);
    return 0;
}