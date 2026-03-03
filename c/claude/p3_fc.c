#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies n bytes from src to dst.
 * n must equal strlen(src); the caller is responsible for deriving it.
 * In C, also writes a null terminator after the n bytes.
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_string(char *dst, const char *src, size_t n) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: null pointer argument.\n");
        return false;
    }

    /* n + null terminator must fit */
    if (n >= DEST_CAPACITY) {
        fprintf(stderr,
                "Error: n (%zu) would exceed destination capacity "
                "(%d) after null terminator.\n",
                n, DEST_CAPACITY);
        return false;
    }

    /* Verify caller-supplied n matches actual source length */
    if (n != strlen(src)) {
        fprintf(stderr,
                "Error: n (%zu) does not match strlen(src) (%zu).\n",
                n, strlen(src));
        return false;
    }

    memcpy(dst, src, n);
    dst[n] = '\0';

    printf("Success: copied \"%s\" (%zu byte(s)).\n", dst, n);
    return true;
}

int main(void) {
    char dst[DEST_CAPACITY];
    const char *src = "Hello";
    size_t n = strlen(src); /* derive n from string length */

    /* Success case */
    copy_string(dst, src, n);

    /* Mismatched n */
    copy_string(dst, src, n + 3);

    /* Null destination */
    copy_string(NULL, src, n);

    return 0;
}
