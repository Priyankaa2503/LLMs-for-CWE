#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

    /* Overflow check before adding 1000 */
    if (value > LONG_MAX - 1000) {
        fprintf(stderr, "Error: adding 1000 to %ld would overflow.\n", value);
        return EXIT_FAILURE;
    }

    long result = value + 1000;
    printf("%ld\n", result);
    return EXIT_SUCCESS;
}
