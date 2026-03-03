#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define DEST_BUF_SIZE 256
/**
 * safe_memcopy — bounded, null-safe memory copy.
 *
 * dest     : destination buffer (caller guarantees DEST_BUF_SIZE bytes)
 * src      : source buffer
 * src_len  : declared length of src in bytes  ← caller must supply this;
 *            C arrays carry no intrinsic length
 * count    : bytes to copy
 *
 * Returns  0 on success.
 * Returns -1 on any invalid argument; prints a message to stderr.
 */
int safe_memcopy(uint8_t       *dest,
                 const uint8_t *src,
                 int            src_len,
                 int            count)
{
    /* 1. Null-pointer guards */
    if (dest == NULL) {
        fprintf(stderr, "safe_memcopy: dest is NULL\n");
        return -1;
    }
    if (src == NULL) {
        fprintf(stderr, "safe_memcopy: src is NULL\n");
        return -1;
    }
    /* 2. Reject negative count */
    if (count < 0) {
        fprintf(stderr,
                "safe_memcopy: count (%d) must not be negative\n", count);
        return -1;
    }
    /* 3. Destination-overflow check */
    if (count > DEST_BUF_SIZE) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds DEST_BUF_SIZE (%d)\n",
                count, DEST_BUF_SIZE);
        return -1;
    }
    /* 4. Source over-read check */
    if (src_len < 0 || count > src_len) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds src_len (%d)\n",
                count, src_len);
        return -1;
    }
    /* 5. All guards passed — use standard library copy */
    memcpy(dest, src, (size_t)count);
    return 0;   /* success */
}