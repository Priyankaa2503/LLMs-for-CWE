/*
 * p13_nc.c - Safe lookup with user-prompted index (C)
 *
 * Reads an index from stdin, validates it, and returns the value at that
 * index within id_sequence, or -1 on invalid input.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int ID_SEQUENCE[] = {10, 20, 30, 40, 50};
#define SEQ_SIZE ((int)(sizeof(ID_SEQUENCE) / sizeof(ID_SEQUENCE[0])))

int lookup_index(int index) {
    if (index < 0 || index >= SEQ_SIZE) {
        return -1;
    }
    return ID_SEQUENCE[index];
}

int main(void) {
    char buffer[64];

    printf("Enter index (0-%d): ", SEQ_SIZE - 1);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 0;
    }

    /* Trim newline */
    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') {
        printf("Result: -1\n");
        return 0;
    }

    errno = 0;
    char *endptr = NULL;
    long index = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
        printf("Result: -1\n");
        return 0;
    }

    if (index < INT_MIN || index > INT_MAX) {
        printf("Result: -1\n");
        return 0;
    }

    int value = lookup_index((int)index);
    printf("Result: %d\n", value);
    return 0;
}

