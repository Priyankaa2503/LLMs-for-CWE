#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define DEST_BUFFER_SIZE 256
/**
 * Copies up to 'count' bytes from 'src' into 'dest'.
 * dest is assumed to be exactly DEST_BUFFER_SIZE (256) bytes.
 *
 * Returns  0 on success.
 * Returns -1 on invalid arguments (NULL pointers, negative or
 *           oversized count, or count exceeds src_len).
 */
int safe_memcopy(
    uint8_t       *dest,
    const uint8_t *src,
    int            src_len,   /* caller-supplied source length */
    int            count)
{
    /* 1. Null-pointer checks */
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "safe_memcopy: NULL pointer argument\n");
        return -1;
    }
    /* 2. Reject negative counts */
    if (count < 0) {
        fprintf(stderr, "safe_memcopy: count must not be negative (%d)\n",
                count);
        return -1;
    }
    /* 3. Destination overflow check */
    if (count > DEST_BUFFER_SIZE) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds destination "
                "buffer size (%d)\n",
                count, DEST_BUFFER_SIZE);
        return -1;
    }
    /* 4. Source overread check (src_len must be provided by caller) */
    if (src_len < 0 || count > src_len) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds source "
                "length (%d)\n",
                count, src_len);
        return -1;
    }
    /* 5. Safe copy using the standard library */
    memcpy(dest, src, (size_t)count);
    return 0; /* success */
}