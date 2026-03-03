#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int *arr, int size, int index) {
    if (arr == NULL || size <= 0 || index < 0 || index >= size)
        return -1;
    return arr[index];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = (int)(sizeof(arr) / sizeof(arr[0]));

    char buf[64];
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 255;

    char *endptr;
    long idx = strtol(buf, &endptr, 10);

    if (endptr == buf || idx < 0 || idx > (long)size - 1)
        return 255; // -1 can't be used as exit code portably; use sentinel

    int result = getValueFromArray(arr, size, (int)idx);
    return (result == -1) ? 255 : result;
}