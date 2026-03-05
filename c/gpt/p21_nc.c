/*
 * p21_nc.c - Safe command-line addition and clean return (C)
 *
 * Reads an argument, parses to integer, adds 1000, prints result, and returns 0.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 1000

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: missing argument.\n");
        return 1;
    }

    const char *input = argv[1];
    char *endptr = NULL;
    errno = 0;
    long value = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return 1;
    }

    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Error: integer out of range.\n");
        return 1;
    }

    if (value > INT_MAX - OFFSET) {
        fprintf(stderr, "Error: addition would overflow.\n");
        return 1;
    }

    int result = (int)value + OFFSET;
    printf("Result: %d\n", result);
    return 0;
}

