/**
 * p4_fc.c - Safe indexed vehicle lookup program (C)
 *
 * Prompts the user for the index of a vehicle, parses the input safely,
 * validates bounds, and prints the corresponding vehicle from a predefined
 * array. Invalid input or out-of-range indices are reported with clear
 * error messages, and no out-of-bounds access is performed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

static const char *VEHICLES[] = {
    "Car",
    "Truck",
    "Bicycle",
    "Motorcycle",
    "Bus"
};

static const size_t NUM_VEHICLES = sizeof(VEHICLES) / sizeof(VEHICLES[0]);

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

    /* Skip optional trailing whitespace. */
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
    printf("Enter the index of a vehicle (0-%zu): ", NUM_VEHICLES - 1);
    fflush(stdout);

    int index = -1;
    if (read_index_from_stdin(&index) != 0) {
        fprintf(stderr, "Exiting due to invalid input.\n");
        return 1;
    }

    if (index < 0 || (size_t)index >= NUM_VEHICLES) {
        fprintf(stderr, "Error: index %d is out of range (valid range is 0-%zu).\n",
                index, NUM_VEHICLES - 1);
        return 1;
    }

    printf("Selected vehicle: %s\n", VEHICLES[index]);
    return 0;
}

