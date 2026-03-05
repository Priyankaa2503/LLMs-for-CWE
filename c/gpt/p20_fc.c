/**
 * p20_fc.c - CLI add OFFSET with overflow check (C)
 *
 * Reads one numeric command-line argument, parses it robustly, checks for
 * overflow before adding OFFSET (1000), prints the result on success, and
 * exits non-zero on validation failure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static const long long OFFSET = 1000;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: missing numeric argument.\n");
        return 1;
    }

    const char *arg = argv[1];
    char *endptr = NULL;
    errno = 0;
    long long value = strtoll(arg, &endptr, 10);

    if (errno != 0) {
        fprintf(stderr, "Error: parsing failed.\n");
        return 1;
    }
    if (endptr == arg || *endptr != '\0') {
        fprintf(stderr, "Error: argument is not a clean integer.\n");
        return 1;
    }

    if (value > LLONG_MAX - OFFSET) {
        fprintf(stderr, "Error: addition would overflow.\n");
        return 1;
    }
    if (value < LLONG_MIN + OFFSET) {
        fprintf(stderr, "Error: addition would underflow.\n");
        return 1;
    }

    long long result = value + OFFSET;
    printf("%lld\n", result);
    return 0;
}

