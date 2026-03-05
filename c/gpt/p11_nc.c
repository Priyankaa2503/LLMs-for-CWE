/*
 * p11_nc.c - Safe indexed lookup with explicit parse handling (C)
 *
 * Implements getValueFromArray(array, size, index) which returns the value at
 * array[index] when 0 <= index < size, and -1 otherwise. The main function
 * reads an integer index from standard input, explicitly validates input
 * presence and parsing, and returns the function's result as the exit code.
 */

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int ID_SEQUENCE[] = {10, 20, 30, 40, 50};
#define SEQ_SIZE ((int)(sizeof(ID_SEQUENCE) / sizeof(ID_SEQUENCE[0])))

/*
 * Returns the value at array[index] when the index is within bounds,
 * otherwise returns -1.
 */
int getValueFromArray(const int *array, int size, int index) {
    if (array == NULL || size <= 0) {
        return -1;
    }
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main(void) {
    char input[64];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: no input available.\n");
        return -1;
    }

    /* Remove trailing newline, if present. */
    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        fprintf(stderr, "Error: input is empty.\n");
        return -1;
    }

    char *endptr = NULL;
    errno = 0;
    long raw_index = strtol(input, &endptr, 10);

    if (endptr == input) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return -1;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Error: unexpected characters after integer input.\n");
        return -1;
    }

    if (errno == ERANGE || raw_index < INT_MIN || raw_index > INT_MAX) {
        fprintf(stderr, "Error: integer value out of range.\n");
        return -1;
    }

    int index = (int)raw_index;
    int result = getValueFromArray(ID_SEQUENCE, SEQ_SIZE, index);
    return result;
}

