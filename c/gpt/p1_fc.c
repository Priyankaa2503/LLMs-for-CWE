/**
 * p1_fc.c - Safe fixed-size byte copy utility (C)
 *
 * Copies exactly n bytes from a source buffer into a 256-byte destination
 * buffer with strict validation. The function:
 *  - rejects NULL pointers
 *  - rejects negative n
 *  - rejects n > 256
 *  - rejects n larger than the known source length
 * On success it copies exactly n bytes and returns 1; on any validation
 * failure it returns 0 and performs no partial copy.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/**
 * Copies exactly n bytes from src into dst.
 *
 * @param dst      destination buffer; must point to at least DEST_CAPACITY bytes
 * @param src      source buffer; must point to at least src_len bytes
 * @param src_len  number of valid bytes available in src
 * @param n        requested number of bytes to copy; validated before use
 * @return true (1) on success, false (0) on any validation failure
 */
bool copy_n_bytes(unsigned char *dst,
                  const unsigned char *src,
                  size_t src_len,
                  int n) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: dst and src must not be NULL.\n");
        return false;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n must not be negative (n=%d).\n", n);
        return false;
    }

    size_t bytes_to_copy = (size_t)n;

    if (bytes_to_copy > DEST_CAPACITY) {
        fprintf(stderr,
                "Error: n (%zu) exceeds fixed destination capacity (%d).\n",
                bytes_to_copy, DEST_CAPACITY);
        return false;
    }

    if (bytes_to_copy > src_len) {
        fprintf(stderr,
                "Error: n (%zu) exceeds available source length (%zu).\n",
                bytes_to_copy, src_len);
        return false;
    }

    for (size_t i = 0; i < bytes_to_copy; ++i) {
        dst[i] = src[i];
    }

    return true;
}

int main(void) {
    unsigned char dst[DEST_CAPACITY] = {0};
    const unsigned char src[] = "Hello, secure world!";
    const size_t src_len = sizeof(src) - 1; /* exclude terminating '\0' */

    /* Successful copy of 5 bytes. */
    if (copy_n_bytes(dst, src, src_len, 5)) {
        printf("Success: copied 5 bytes: '");
        for (int i = 0; i < 5; ++i) {
            putchar((char)dst[i]);
        }
        printf("'\n");
    } else {
        printf("Unexpected failure for valid copy.\n");
    }

    /* Failure: attempt to copy more than capacity. */
    if (!copy_n_bytes(dst, src, src_len, 300)) {
        printf("Correctly rejected invalid copy request (n=300).\n");
    } else {
        printf("Unexpected success for invalid copy.\n");
    }

    return 0;
}

