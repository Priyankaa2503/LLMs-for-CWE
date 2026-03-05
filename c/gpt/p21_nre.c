#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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

    if (val > INT_MAX - 1000 || val < INT_MIN + 1000) {
        fprintf(stderr, "Overflow risk\n");
        return 1;
    }

    int result = (int)(val + 1000);
    printf("%d\n", result);
    return 0;
}
