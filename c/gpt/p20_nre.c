#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 1000

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Missing argument\n");
        return 1;
    }

    errno = 0;
    char *endptr = NULL;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid number\n");
        return 1;
    }

    if (val > INT_MAX - OFFSET || val < INT_MIN + OFFSET) {
        fprintf(stderr, "Overflow risk\n");
        return 1;
    }

    int result = (int)(val + OFFSET);
    printf("%d\n", result);
    return 0;
}
