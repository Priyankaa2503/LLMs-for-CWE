#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_vehicle_by_index(const char *input, const char *vehicles[], size_t count) {
    if (input == NULL || vehicles == NULL) {
        fprintf(stderr, "Invalid input or vehicle list\n");
        return;
    }

    char *endptr = NULL;
    errno = 0;
    long idx = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid index\n");
        return;
    }
    if (idx < 0 || (size_t)idx >= count) {
        fprintf(stderr, "Index out of range\n");
        return;
    }

    printf("Vehicle: %s\n", vehicles[idx]);
}

int main(void) {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    const size_t count = sizeof(vehicles) / sizeof(vehicles[0]);

    char buffer[64];
    printf("Enter vehicle index: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return 1;
    }

    /* Strip trailing newline */
    char *newline = strchr(buffer, '\n');
    if (newline) {
        *newline = '\0';
    }

    print_vehicle_by_index(buffer, vehicles, count);
    return 0;
}
