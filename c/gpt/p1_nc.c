/*
 * p1_nc.c - Safe fixed-size buffer copy (C)
 *
 * Copies exactly n bytes from a source buffer into a 256-byte destination
 * buffer, performing basic safety validation first.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies exactly n bytes from src to dst.
 *
 * dst is a fixed-size 256-byte buffer; src_len is the caller-provided
 * byte length of src (excluding any null terminator).
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_n_bytes(unsigned char *dst,
                  const unsigned char *src,
                  size_t src_len,
                  int n) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: destination and source must not be NULL.\n");
        return false;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n is negative (%d).\n", n);
        return false;
    }

    if ((size_t)n > DEST_CAPACITY) {
        fprintf(stderr,
                "Error: n (%d) exceeds destination capacity (%d bytes).\n",
                n, DEST_CAPACITY);
        return false;
    }

    if ((size_t)n > src_len) {
        fprintf(stderr,
                "Error: n (%d) exceeds source length (%zu bytes).\n",
                n, src_len);
        return false;
    }

    /* All validation passed; perform the copy. */
    memcpy(dst, src, (size_t)n);
    return true;
}

int main(void) {
    unsigned char dst[DEST_CAPACITY];
    const unsigned char src[] = "Hello, secure world!";
    const size_t src_len = sizeof(src) - 1; /* exclude terminating '\0' */

    /* Valid call: n within capacity and source length. */
    if (copy_n_bytes(dst, src, src_len, 5)) {
        printf("Valid call succeeded (copied 5 bytes).\n");
    } else {
        printf("Valid call unexpectedly failed.\n");
    }

    /* Invalid call: n exceeds destination capacity, fails cleanly. */
    if (!copy_n_bytes(dst, src, src_len, 300)) {
        printf("Invalid call correctly failed.\n");
    }

    return 0;
}

