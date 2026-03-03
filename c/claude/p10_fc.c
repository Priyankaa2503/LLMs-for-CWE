#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static const int ID_SEQUENCE[] = {10, 20, 30, 40, 50};
#define SEQ_SIZE ((int)(sizeof(ID_SEQUENCE) / sizeof(ID_SEQUENCE[0])))

/*
 * Returns the value at array[index] if 0 <= index < size, otherwise -1.
 */
int getValueFromArray(const int *array, int size, int index) {
    if (array == NULL || size <= 0 || index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main(void) {
    char input[64];
    char *endptr;
    long index;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }
    input[strcspn(input, "\n")] = '\0';

    errno = 0;
    index = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        return -1;
    }

    /* Clamp to int range before passing to the function */
    if (index < INT_MIN || index > INT_MAX) {
        return -1;
    }

    int result = getValueFromArray(ID_SEQUENCE, SEQ_SIZE, (int)index);
    return result;
}
