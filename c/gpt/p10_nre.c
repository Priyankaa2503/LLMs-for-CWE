#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int getValueFromArray(const int *arr, size_t size, size_t idx) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    if (idx >= size) {
        return -1;
    }
    return arr[idx];
}

int main(void) {
    const int id_sequence[] = {10, 20, 30, 40, 50};
    const size_t size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    char buffer[64];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *endptr = NULL;
    errno = 0;
    long parsed = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || (*endptr != '\0' && *endptr != '\n') || parsed < 0) {
        return -1;
    }

    int result = getValueFromArray(id_sequence, size, (size_t)parsed);
    return result;
}
