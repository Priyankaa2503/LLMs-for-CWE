#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define OFFSET 1000L

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long value = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Overflow check before adding the offset */
    if (value > LONG_MAX - OFFSET) {
        fprintf(stderr, "Error: adding %ld to %ld would overflow.\n", OFFSET, value);
        return EXIT_FAILURE;
    }

    long result = value + OFFSET;
    printf("%ld\n", result);
    return EXIT_SUCCESS;
}
