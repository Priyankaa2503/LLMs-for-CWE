#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int getValueFromArray(const int *arr, int size, int index) {
    if (!arr || size <= 0 || index < 0 || index >= size) return -1;
    return arr[index];
}

int main(void) {
    char buf[64];

    /* Read line safely, reject missing or empty input */
    if (!fgets(buf, sizeof(buf), stdin)) return -1;
    buf[strcspn(buf, "\n")] = '\0';
    if (buf[0] == '\0') return -1;

    /* Safe integer parsing: rejects floats, trailing chars, overflow */
    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);
    if (errno != 0 || endptr == buf || *endptr != '\0') return -1;
    if (val < -2147483648L || val > 2147483647L)        return -1;

    int size = (int)(sizeof(id_sequence) / sizeof(id_sequence[0]));
    return getValueFromArray(id_sequence, size, (int)val);
}