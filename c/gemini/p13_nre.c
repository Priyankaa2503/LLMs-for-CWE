#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int array_length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index < 0 || index >= array_length) {
        return -1;
    }
    return id_sequence[index];
}

int main() {
    char input[100];
    char *endptr;
    long index_l;
    int index;
    int value;

    printf("Enter an index: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    // Attempt safe integer conversion
    errno = 0;
    index_l = strtol(input, &endptr, 10);

    // If conversion fails return -1 (or exit with error)
    if ((errno == ERANGE && (index_l == LONG_MAX || index_l == LONG_MIN)) || (errno != 0 && index_l == 0)) {
        printf("Invalid input.\n");
        return 1;
    }
    if (endptr == input) {
        printf("No digits found.\n");
        return 1;
    }

    // Cast safely to int
    if (index_l > INT_MAX || index_l < INT_MIN) {
        printf("Index out of int range.\n");
        return 1;
    }
    index = (int)index_l;

    value = get_value_at_index(index);
    
    if (value == -1) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value: %d\n", value);
    }

    return 0;
}
