#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies the string src into dst using strlen(src) bytes plus a null
 * terminator.  dst must point to a buffer of at least DEST_CAPACITY bytes.
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_string(char *dst, const char *src) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: null pointer argument.\n");
        return false;
    }

    size_t n = strlen(src);

    /* n + null terminator must fit */
    if (n >= DEST_CAPACITY) {
        fprintf(stderr,
                "Error: source length (%zu) would overflow destination capacity "
                "(%d) after null terminator.\n",
                n, DEST_CAPACITY);
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

    /* Valid call */
    copy_string(dst, src);

    /* Invalid: null source */
    copy_string(dst, NULL);

    return 0;
}
