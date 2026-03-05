#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Bus", "Train", "Plane"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[50];

    printf("Enter the index of the vehicle (0-%d): ", num_vehicles - 1);
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    // Remove newline character if present
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("Error: Input cannot be empty.\n");
        return 1;
    }

    char *endptr;
    long index = strtol(input, &endptr, 10);

    // Check for conversion errors
    if (endptr == input || *endptr != '\0') {
        printf("Error: Invalid input. Please enter a valid integer.\n");
        return 1;
    }

    // Check range
    if (index < 0 || index >= num_vehicles) {
        printf("Error: Index out of bounds. Must be between 0 and %d.\n", num_vehicles - 1);
        return 1;
    }

    printf("Selected vehicle: %s\n", vehicles[index]);

    return 0;
}
