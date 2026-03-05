#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int getValueFromArray(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index < 0 || index >= size) {
        return -1;
    }
    return id_sequence[index];
}

int main() {
    char input[256];
    printf("Enter index: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    char *endptr;
    errno = 0;
    long index = strtol(input, &endptr, 10);

    if (errno != 0 || input == endptr) {
        printf("Invalid input\n");
        return 1;
    }

    int result = getValueFromArray((int)index);
    printf("Value: %d\n", result);

    return 0;
}
