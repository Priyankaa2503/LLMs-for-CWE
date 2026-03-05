#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer argument.\n");
        return 1;
    }

    // Check for overflow before adding 1000
    if (val > INT_MAX - 1000) {
        fprintf(stderr, "Error: Integer overflow.\n");
        return 1;
    }
    
    // Also check for underflow if val is negative, though adding 1000 usually moves away from MIN
    // strictly speaking: if val < INT_MIN + 1000 (not possible if val is long and we check against INT_MAX)
    // We'll assume we are working within int range.

    int result = (int)val + 1000;
    printf("%d\n", result);

    return 0;
}
