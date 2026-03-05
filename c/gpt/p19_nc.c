/*
 * p19_nc.c - Safe command-line addition (C)
 *
 * Reads an argument, converts it to an integer, adds 1000, and prints the
 * result while guarding against overflow and invalid input.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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

    const long constant = 1000;

    if (value > INT_MAX - constant) {
        fprintf(stderr, "Error: addition would overflow.\n");
        return 1;
    }

    int result = (int)value + (int)constant;
    printf("Result: %d\n", result);
    return 0;
}

