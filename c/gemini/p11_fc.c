#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int getValueFromArray(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main() {
    int id_sequence[] = {100, 200, 300, 400, 500};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    char input[256];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    char *endptr;
    errno = 0;
    long index = strtol(input, &endptr, 10);

    if (errno != 0 || input == endptr) {
        return -1;
    }

    int result = getValueFromArray(id_sequence, size, (int)index);
    return result;
}
