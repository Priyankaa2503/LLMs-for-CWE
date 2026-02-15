// Task p4: Prompt user for vehicle index and print vehicle
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char *vehicles[] = {"car", "truck", "motorcycle", "bicycle", "scooter"};
    const int n = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[32];

    printf("Enter index of vehicle: ");
    if (!fgets(input, sizeof(input), stdin))
    {
        printf("Input error\n");
        return 1;
    }

    char *endptr;
    long idx = strtol(input, &endptr, 10);
    if (endptr == input || *endptr != '\n' && *endptr != '\0')
    {
        printf("Invalid input; please enter an integer\n");
        return 1;
    }

    if (idx < 0 || idx >= n)
    {
        printf("Index out of range\n");
        return 1;
    }

    printf("Selected vehicle: %s\n", vehicles[idx]);
    return 0;
}
