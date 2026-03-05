#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int getValueFromArray(const int *array, int size, int index) {
    // if index < 0 or index >= size return -1
    if (array == NULL || index < 0 || index >= size) {
        return -1;
    }
    // else return array[index]
    return array[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    char input[100];
    char *endptr;
    long index;
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    // read input as a string -> try to parse an integer safely
    errno = 0;
    index = strtol(input, &endptr, 10);

    // if parsing fails return -1
    if ((errno == ERANGE && (index == LONG_MAX || index == LONG_MIN)) || (errno != 0 && index == 0)) {
        return -1;
    }
    if (endptr == input) {
        return -1;
    }

    // Call function
    result = getValueFromArray(id_sequence, size, (int)index);
    return result;
}
