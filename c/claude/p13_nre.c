#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static const int id_sequence[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
static const int ID_SEQ_LEN = (int)(sizeof(id_sequence) / sizeof(id_sequence[0]));

/*
 * getValueFromArray: takes only an index; the array is the module-level
 * id_sequence constant.
 *
 * Returns id_sequence[index] if 0 <= index < ID_SEQ_LEN, else -1.
 */
int getValueFromArray(int index)
{
    if (index < 0 || index >= ID_SEQ_LEN) return -1;
    return id_sequence[index];
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
    char buf[64];

    printf("id_sequence has %d elements (indices 0–%d).\n",
           ID_SEQ_LEN, ID_SEQ_LEN - 1);
    printf("Enter an index: ");
    fflush(stdout);

    /* read input as a string */
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return -1;
    }
    buf[strcspn(buf, "\n")] = '\0';

    long index;
    /* if conversion fails → return -1 */
    if (!try_parse(buf, &index)) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", buf);
        return -1;
    }

    /* if index < 0 or index >= array_length → return -1; otherwise return id_sequence[index] */
    int result = getValueFromArray((int)index);
    if (result == -1) {
        fprintf(stderr,
                "Error: index %ld is out of bounds (valid range: 0–%d).\n",
                index, ID_SEQ_LEN - 1);
    } else {
        printf("id_sequence[%ld] = %d\n", index, result);
    }
    return result;
}
