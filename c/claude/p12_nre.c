#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * getValueFromArray: returns arr[index] if 0 <= index < size, else -1.
 * Returns -1 immediately for a NULL pointer or non-positive size.
 */
int getValueFromArray(const int *arr, int size, int index)
{
    if (arr == NULL || size <= 0) return -1;
    if (index < 0 || index >= size) return -1;
    return arr[index];
}

/*
 * try_parse: wraps strtol with full validation.
 * Returns 1 and sets *out on success; 0 on any failure.
 */
static int try_parse(const char *str, long *out)
{
    if (str == NULL || *str == '\0') return 0;
    char *end;
    errno = 0;
    long v = strtol(str, &end, 10);
    if (errno != 0 || end == str || *end != '\0') return 0;
    *out = v;
    return 1;
}

int main(void)
{
    static const int id_sequence[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    static const int SIZE = (int)(sizeof(id_sequence) / sizeof(id_sequence[0]));

    char buf[64];
    /* read input as a string */
    if (fgets(buf, sizeof(buf), stdin) == NULL) return -1;

    /* strip newline */
    buf[strcspn(buf, "\n")] = '\0';

    long index;
    /* if parsing fails → return -1 */
    if (!try_parse(buf, &index)) return -1;

    /* if index < 0 or index >= size → return -1; else return array[index] */
    return getValueFromArray(id_sequence, SIZE, (int)index);
}
