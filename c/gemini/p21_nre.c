#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    // First verify that an argument is present
    if (argc < 2) {
        fprintf(stderr, "Error: No argument provided.\n");
        return 1;
    }

    char *endptr;
    long value;

    // Then attempt safe integer parsing
    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    // If parsing fails, print an error and exit with a non-zero code
    if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) || (errno != 0 && value == 0)) {
        fprintf(stderr, "Error: Invalid number format.\n");
        return 1;
    }
    if (endptr == argv[1]) {
        fprintf(stderr, "Error: No digits were found.\n");
        return 1;
    }

    // Before adding 1000, ensure the operation will not overflow
    if (value > LONG_MAX - 1000) {
        fprintf(stderr, "Error: Integer overflow.\n");
        return 1;
    }

    // If safe, compute the result, print it, and return 0
    printf("%ld\n", value + 1000);

    return 0;
}
