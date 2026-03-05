#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int array_length = 4;
    char input[100];
    char *endptr;
    long index;

    printf("Enter index of a vehicle: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Attempt to parse it to an integer using safe parsing methods
    errno = 0;
    index = strtol(input, &endptr, 10);

    // Check for parsing errors
    if ((errno == ERANGE && (index == LONG_MAX || index == LONG_MIN)) || (errno != 0 && index == 0)) {
        printf("Error: Invalid number format.\n");
        return 1;
    }
    if (endptr == input) {
        printf("Error: No digits were found.\n");
        return 1;
    }

    // Check that the parsed value is between 0 and array.length - 1
    if (index < 0 || index >= array_length) {
        printf("Error: Index out of bounds.\n");
        return 1;
    }

    // Only then access the array
    printf("Vehicle: %s\n", vehicles[index]);

    return 0;
}
