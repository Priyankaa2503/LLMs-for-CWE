#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main() {
    const char *vehicles[] = {"Car", "Truck", "Motorcycle", "Bus", "Bicycle"};
    int vehicle_count = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[64];

    printf("Enter the index of a vehicle: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    /* Strip trailing newline */
    input[strcspn(input, "\n")] = '\0';

    /* Check for empty or whitespace-only input */
    int all_space = 1;
    for (int i = 0; input[i]; i++) {
        if (!isspace((unsigned char)input[i])) { all_space = 0; break; }
    }
    if (all_space) {
        printf("Error: Input cannot be empty.\n");
        return 1;
    }

    /* Safely convert to integer using strtol */
    char *endptr;
    errno = 0;
    long index = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0') {
        printf("Error: Please enter a valid integer.\n");
        return 1;
    }

    /* Bounds check before array access */
    if (index < 0 || index >= vehicle_count) {
        printf("Error: Index out of range. Valid range is 0 to %d.\n", vehicle_count - 1);
        return 1;
    }

    printf("Vehicle at index %ld: %s\n", index, vehicles[index]);
    return 0;
}