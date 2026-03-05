#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getValueFromArray(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    char input[50];

    printf("Enter an index: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    // Remove newline
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("Error: Input cannot be empty.\n");
        return -1;
    }

    char *endptr;
    long index_l = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\0') {
        printf("Error: Invalid integer input.\n");
        return -1;
    }

    // Cast to int for the function, checking bounds first
    if (index_l < 0 || index_l >= size) {
        printf("Error: Index out of bounds.\n");
        return -1;
    }

    int result = getValueFromArray(id_sequence, size, (int)index_l);
    printf("Value at index %ld: %d\n", index_l, result);

    return 0;
}
