#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * getValueFromArray: safely retrieves the element at index from arr.
 *
 * Returns the element value on success.
 * Returns -1 if arr is NULL, size <= 0, or index is out of bounds.
 */
int getValueFromArray(const int *arr, int size, int index)
{
    if (arr == NULL || size <= 0) {
        fprintf(stderr, "Error: invalid array or size.\n");
        return -1;
    }

    if (index < 0 || index >= size) {
        fprintf(stderr,
                "Error: index %d is out of bounds (valid range: 0–%d).\n",
                index, size - 1);
        return -1;
    }

    return arr[index];
}

/*
 * safe_parse_int: converts a string to a long via strtol.
 *
 * Returns 1 and writes the value to *out on success.
 * Returns 0 on empty input, non-numeric characters, or overflow.
 */
static int safe_parse_int(const char *str, long *out)
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
    static const int id_sequence[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    static const int SEQ_SIZE = (int)(sizeof(id_sequence) / sizeof(id_sequence[0]));

    char input[64];

    printf("id_sequence has %d elements (indices 0–%d).\n", SEQ_SIZE, SEQ_SIZE - 1);
    printf("Enter an index: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return -1;
    }
    trim_newline(input);

    long index;
    if (!safe_parse_int(input, &index)) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return -1;
    }

    /* Cast is safe: safe_parse_int already caught overflow outside int range */
    int result = getValueFromArray(id_sequence, SEQ_SIZE, (int)index);

    printf("Result: %d\n", result);
    return result;
}
