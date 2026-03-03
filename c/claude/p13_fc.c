#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static const int id_sequence[] = {10, 20, 30, 40, 50};
#define SEQ_SIZE ((int)(sizeof(id_sequence) / sizeof(id_sequence[0])))

/*
 * Returns id_sequence[index] when 0 <= index < SEQ_SIZE, otherwise -1.
 */
int getValueByIndex(int index) {
    if (index < 0 || index >= SEQ_SIZE) {
        return -1;
    }
    return id_sequence[index];
}

int main(void) {
    char input[64];
    char *endptr;
    long idx;

    printf("Enter index (0-%d): ", SEQ_SIZE - 1);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';

    errno = 0;
    idx = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\0' || errno == ERANGE ||
        idx < INT_MIN || idx > INT_MAX) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return EXIT_FAILURE;
    }

    int result = getValueByIndex((int)idx);
    printf("Result: %d\n", result);
    return EXIT_SUCCESS;
}
