/**
 * p13_fc.c - Safe index lookup program (C)
 *
 * Defines get_value_at_index, which returns the element at the provided
 * index from a predefined id_sequence array, or -1 if the index is out of
 * bounds. Main prompts for an index, safely parses input, performs strict
 * bounds checking, and prints the result. Invalid or out-of-range inputs
 * return -1 and avoid any undefined behavior.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static const int id_sequence[] = {3, 6, 9, 12, 15};
static const size_t id_sequence_len = sizeof(id_sequence) / sizeof(id_sequence[0]);

static int get_value_at_index(int index) {
    if (index < 0 || (size_t)index >= id_sequence_len) {
        return -1;
    }
    return id_sequence[index];
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
        fprintf(stderr, "Error: no digits were found.\n");
        return -1;
    }
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
    printf("Enter an index: ");
    fflush(stdout);

    int idx = -1;
    if (read_index_from_stdin(&idx) != 0) {
        printf("-1\n");
        return 0;
    }

    int result = get_value_at_index(idx);
    printf("%d\n", result);
    return 0;
}

