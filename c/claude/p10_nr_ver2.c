#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static const int id_sequence[] = {10, 20, 30, 40, 50};
static const int id_sequence_size = sizeof(id_sequence) / sizeof(id_sequence[0]);

int getValueFromArray(const int *arr, int size, int index) {
    if (arr == NULL || size <= 0 || index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
}

int main(void) {
    char buf[64];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return -1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (endptr == buf || errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return -1;
    }

    int result = getValueFromArray(id_sequence, id_sequence_size, (int)val);
    return result;
}