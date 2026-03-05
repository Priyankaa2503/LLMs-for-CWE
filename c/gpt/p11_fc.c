/**
 * p11_fc.c - Safe getValueFromArray with exit code (C)
 *
 * Defines getValueFromArray(array, size, index) which returns the value at
 * the given index when 0 <= index < size, and returns -1 otherwise. The
 * main function reads an integer from standard input, parses it robustly,
 * calls getValueFromArray using a predefined id_sequence array, and exits
 * with the function's result as the program exit code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static const int ID_SEQUENCE[] = {100, 200, 300, 400, 500};
static const size_t ID_SEQUENCE_SIZE = sizeof(ID_SEQUENCE) / sizeof(ID_SEQUENCE[0]);

int getValueFromArray(const int *array, size_t size, int index) {
    if (array == NULL) {
        return -1;
    }
    if (index < 0 || (size_t)index >= size) {
        return -1;
    }
    return array[index];
}

static int read_index_from_stdin(int *out_index) {
    char buffer[64];

    if (out_index == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return -1;
    }

    char *endptr = NULL;
    errno = 0;
    long value = strtol(buffer, &endptr, 10);

    if (errno != 0) {
        fprintf(stderr, "Error: integer parsing failed.\n");
        return -1;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Error: no digits were found in input.\n");
        return -1;
    }

    /* Skip trailing whitespace. */
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        ++endptr;
    }

    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Error: invalid trailing characters in input.\n");
        return -1;
    }

    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Error: parsed integer is out of range.\n");
        return -1;
    }

    *out_index = (int)value;
    return 0;
}

int main(void) {
    int index = -1;
    int result = -1;

    if (read_index_from_stdin(&index) != 0) {
        /* Parsing failed; do not access the array. */
        result = -1;
    } else {
        result = getValueFromArray(ID_SEQUENCE, ID_SEQUENCE_SIZE, index);
    }

    return result;
}

