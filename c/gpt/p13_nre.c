#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int getValueFromArray(const int *arr, size_t size, size_t idx) {
    if (arr == NULL || size == 0 || idx >= size) {
        return -1;
    }
    return arr[idx];
}

int main(void) {
    const int id_sequence[] = {4, 8, 15, 16, 23, 42};
    const size_t size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    char buffer[64];
    printf("Enter index: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    char *endptr = NULL;
    long parsed = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || (*endptr != '\0' && *endptr != '\n') || parsed < 0) {
        return -1;
    }

    return getValueFromArray(id_sequence, size, (size_t)parsed);
}
