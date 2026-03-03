#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No argument provided. Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long value = strtol(argv[1], &endptr, 10);

    if (errno != 0) {
        fprintf(stderr, "Error: Value out of range.\n");
        return 1;
    }
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer: '%s'\n", argv[1]);
        return 1;
    }

    // Overflow check before adding 1000
    if (value > LONG_MAX - 1000) {
        fprintf(stderr, "Error: Integer overflow would occur.\n");
        return 1;
    }

    value += 1000;
    printf("%ld\n", value);
    return 0;
}