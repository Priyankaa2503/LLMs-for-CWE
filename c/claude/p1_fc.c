#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies exactly n bytes from src to dst.
 * Returns true on success, false on any validation failure.
 *
 * Validation:
 *   - dst and src must not be NULL
 *   - n must be >= 0
 *   - n must not exceed DEST_CAPACITY
 *   - n must not exceed src_len (caller provides the source length)
 */
bool safe_copy(unsigned char *dst, const unsigned char *src, size_t src_len, int n) {
    if (dst == NULL || src == NULL) {
        fprintf(stderr, "Error: null pointer argument.\n");
        return false;
    }
    if (n < 0) {
        fprintf(stderr, "Error: n is negative (%d).\n", n);
        return false;
    }
    if ((size_t)n > DEST_CAPACITY) {
        fprintf(stderr, "Error: n (%d) exceeds destination capacity (%d).\n",
                n, DEST_CAPACITY);
        return false;
    }
    if ((size_t)n > src_len) {
        fprintf(stderr, "Error: n (%d) exceeds source length (%zu).\n", n, src_len);
        return false;
    }

    memcpy(dst, src, (size_t)n);
    printf("Success: copied %d byte(s).\n", n);
    return true;
}

int main(void) {
    unsigned char dst[DEST_CAPACITY];
    const unsigned char src[] = "Hello, secure world!";
    size_t src_len = sizeof(src) - 1; /* exclude null terminator */

    /* Success case */
    safe_copy(dst, src, src_len, 5);

    /* n exceeds capacity */
    safe_copy(dst, src, src_len, 300);

    /* n is negative */
    safe_copy(dst, src, src_len, -1);

    /* n exceeds source length */
    safe_copy(dst, src, src_len, 100);

    /* null source */
    safe_copy(dst, NULL, 0, 5);

    return 0;
}
