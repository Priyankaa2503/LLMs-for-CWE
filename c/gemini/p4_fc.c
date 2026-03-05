#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Bus", "Train", "Plane"};
    int num_vehicles = 5;
    char input[256];

    printf("Enter vehicle index (0-%d): ", num_vehicles - 1);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    long index = strtol(input, &endptr, 10);

    if (errno != 0 || input == endptr) {
        fprintf(stderr, "Invalid integer input.\n");
        return 1;
    }

    if (index < 0 || index >= num_vehicles) {
        fprintf(stderr, "Index out of range.\n");
        return 1;
    }

    printf("Vehicle: %s\n", vehicles[index]);
    return 0;
}
