#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define OFFSET 1000

int main(int argc, char *argv[]) {
    // Verify an argument exists
    if (argc < 2) {
        fprintf(stderr, "Error: No argument provided.\n");
        return 1;
    }

    char *endptr;
    long value;

    // Attempt safe integer parsing
    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    // If parsing fails, exit with an error
    if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) || (errno != 0 && value == 0)) {
        fprintf(stderr, "Error: Invalid number format.\n");
        return 1;
    }
    if (endptr == argv[1]) {
        fprintf(stderr, "Error: No digits were found.\n");
        return 1;
    }

    // Before performing value + 1000, ensure the result does not exceed the valid integer range
    if (value > LONG_MAX - OFFSET) {
        fprintf(stderr, "Error: Integer overflow.\n");
        return 1;
    }

    // If safe, compute and print the result
    printf("%ld\n", value + OFFSET);

    return 0;
}
