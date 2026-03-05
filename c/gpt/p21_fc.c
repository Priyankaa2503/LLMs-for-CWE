/**
 * p21_fc.c - CLI add 1000 with overflow check (C)
 *
 * Reads one numeric command-line argument, parses it robustly, checks for
 * overflow before adding 1000, prints the result on success, returns 0, and
 * exits non-zero on any validation failure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static const long long ADDEND = 1000;

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

    if (value > LLONG_MAX - ADDEND) {
        fprintf(stderr, "Error: addition would overflow.\n");
        return 1;
    }
    if (value < LLONG_MIN + ADDEND) {
        fprintf(stderr, "Error: addition would underflow.\n");
        return 1;
    }

    long long result = value + ADDEND;
    printf("%lld\n", result);
    return 0;
}

