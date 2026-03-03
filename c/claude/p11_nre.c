#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * getValueFromArray: returns arr[index] if 0 <= index < size, else -1.
 *
 * Also returns -1 if arr is NULL or size is not positive.
 */
int getValueFromArray(const int *arr, int size, int index)
{
    if (arr == NULL || size <= 0) return -1;
    if (index < 0 || index >= size) return -1;
    return arr[index];
}

/*
 * parse_int: converts str to a long via strtol.
 *
 * Returns 1 and writes the result to *out on success.
 * Returns 0 on empty input, trailing non-digits, or overflow.
 */
static int parse_int(const char *str, long *out)
{
    if (str == NULL || *str == '\0') return 0;

    char *endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);

    if (errno != 0 || endptr == str || *endptr != '\0') return 0;

    *out = value;
    return 1;
}

static void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

int main(void)
{
    static const int id_sequence[] = {100, 200, 300, 400, 500, 600, 700, 800};
    static const int SIZE = (int)(sizeof(id_sequence) / sizeof(id_sequence[0]));

    char input[64];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        /* if parsing fails → return -1 */
        return -1;
    }
    trim_newline(input);

    long index;
    /* if parsing fails → return -1 */
    if (!parse_int(input, &index)) return -1;

    /* if index out of bounds → return -1; else return array[index] */
    int result = getValueFromArray(id_sequence, SIZE, (int)index);
    return result;
}
