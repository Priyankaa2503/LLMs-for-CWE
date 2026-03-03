#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static const char *VEHICLES[] = {
    "Car", "Truck", "Motorcycle", "Bus", "Bicycle"
};

#define NUM_VEHICLES ((int)(sizeof(VEHICLES) / sizeof(VEHICLES[0])))

int main(void) {
    char input[64];
    char *endptr;
    long index;

    printf("Enter vehicle index (0-%d): ", NUM_VEHICLES - 1);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Remove trailing newline */
    input[strcspn(input, "\n")] = '\0';

    errno = 0;
    index = strtol(input, &endptr, 10);

    /* Conversion failed: no digits consumed, or trailing non-numeric chars */
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return EXIT_FAILURE;
    }
    /* Overflow/underflow */
    if (errno == ERANGE || index < 0 || index >= NUM_VEHICLES) {
        fprintf(stderr, "Error: index %ld is out of range (0-%d).\n",
                index, NUM_VEHICLES - 1);
        return EXIT_FAILURE;
    }

    printf("Vehicle: %s\n", VEHICLES[(size_t)index]);
    return EXIT_SUCCESS;
}
