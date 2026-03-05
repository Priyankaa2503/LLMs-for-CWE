/*
 * p4_nc.c - Safe vehicle index input and array access (C)
 *
 * Prompts the user for an index, safely parses it as an integer, validates
 * range, and prints the selected vehicle without causing out-of-bounds
 * access or undefined behavior.
 */

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *VEHICLES[] = {
    "Car",
    "Truck",
    "Motorcycle",
    "Bus",
    "Bicycle",
};

static const size_t VEHICLE_COUNT = sizeof(VEHICLES) / sizeof(VEHICLES[0]);

/* Helper to trim trailing newline characters from fgets input. */
static void trim_newline(char *s) {
    if (s == NULL) {
        return;
    }
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

int main(void) {
    char buffer[64];

    printf("Enter vehicle index (0-%zu): ", VEHICLE_COUNT - 1);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: no input available.\n");
        return 1;
    }

    trim_newline(buffer);

    if (buffer[0] == '\0') {
        fprintf(stderr, "Error: input is empty.\n");
        return 1;
    }

    char *endptr = NULL;
    errno = 0;
    long value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", buffer);
        return 1;
    }

    /* Ensure no unexpected trailing characters */
    while (*endptr == ' ' || *endptr == '\t') {
        ++endptr;
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Error: extra characters after integer input.\n");
        return 1;
    }

    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Error: integer out of range.\n");
        return 1;
    }

    if (value < 0) {
        fprintf(stderr, "Error: index must be non-negative.\n");
        return 1;
    }

    if ((size_t)value >= VEHICLE_COUNT) {
        fprintf(stderr,
                "Error: index %ld is out of range (0-%zu).\n",
                value, VEHICLE_COUNT - 1);
        return 1;
    }

    /* Now it is safe to index the array. */
    printf("Vehicle: %s\n", VEHICLES[value]);
    return 0;
}

