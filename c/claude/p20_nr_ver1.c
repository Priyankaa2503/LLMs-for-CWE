#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define OFFSET 1000

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No argument provided. Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long value = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer input: \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Overflow check before adding offset
    if (value > LONG_MAX - OFFSET) {
        fprintf(stderr, "Error: Integer overflow would occur (%ld + %d).\n", value, OFFSET);
        return EXIT_FAILURE;
    }

    long result = value + OFFSET;
    printf("Result: %ld\n", result);
    return EXIT_SUCCESS;
}