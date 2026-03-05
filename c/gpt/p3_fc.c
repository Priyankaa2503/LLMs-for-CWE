/**
 * p3_fc.c - Copy string using computed length with explicit n parameter (C)
 *
 * Implements a function that copies a source string (e.g., "Hello") into a
 * fixed-size destination buffer. The function takes destination, source,
 * and an explicit number-of-bytes parameter, but it *derives* the actual
 * copy length from strlen(source) to avoid trusting the caller-provided n.
 *
 * Validation:
 *  - destination and source must not be NULL
 *  - computed length must fit within DEST_CAPACITY - 1 (for NUL terminator)
 *  - for clarity, n must not be negative (though it is otherwise ignored)
 *
 * On success, the function copies exactly strlen(source) bytes and appends
 * a terminating '\0'. On failure, it returns 0 and performs no partial copy.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DEST_CAPACITY 256

/**
 * Copies a source string into dst using its computed length.
 *
 * @param dst destination buffer; must point to at least DEST_CAPACITY bytes
 * @param src NUL-terminated source string
 * @param n   caller-supplied "number of bytes" (validated for negativity but
 *            not trusted for the copy length)
 * @return true (1) on success, false (0) on validation failure
 */
bool copy_string_with_length(char *dst, const char *src, int n) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: destination and source must not be NULL.\n");
        return false;
    }

    if (n < 0) {
        fprintf(stderr, "Error: number-of-bytes parameter must not be negative (n=%d).\n", n);
        return false;
    }

    size_t len = strlen(src);

    if (len >= DEST_CAPACITY) {
        fprintf(stderr,
                "Error: source length (%zu) does not fit in %d-byte buffer "
                "with space for NUL terminator.\n",
                len, DEST_CAPACITY);
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        dst[i] = src[i];
    }
    dst[len] = '\0';

    return true;
}

int main(void) {
    char dst[DEST_CAPACITY];
    const char *hello = "Hello";

    /* Successful copy. */
    if (copy_string_with_length(dst, hello, 5)) {
        printf("Success: '%s'\n", dst);
    } else {
        printf("Unexpected failure for valid input.\n");
    }

    /* Failure: overly long string that would overflow the buffer. */
    char long_message[300];
    memset(long_message, 'B', sizeof(long_message) - 1);
    long_message[sizeof(long_message) - 1] = '\0';

    if (!copy_string_with_length(dst, long_message, 10)) {
        printf("Correctly rejected overly long source string.\n");
    } else {
        printf("Unexpected success for overly long source string.\n");
    }

    return 0;
}

