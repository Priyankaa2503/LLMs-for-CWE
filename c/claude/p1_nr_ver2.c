#include <string.h>
#include <stdint.h>
#include <stdio.h>
#define DEST_SIZE 256
/**
 * Copies 'count' bytes from 'src' into 'dest'.
 *
 * dest     - destination buffer, must be exactly DEST_SIZE bytes
 * src      - source buffer supplied by the caller
 * src_len  - caller-declared length of src in bytes
 * count    - number of bytes to copy
 *
 * Returns  0 on success.
 * Returns -1 on any invalid argument (message printed to stderr).
 *
 * NOTE: C arrays carry no intrinsic length; the caller must supply
 * src_len so the function can detect source over-reads.
 */
int safe_memcopy(uint8_t *dest,
                 const uint8_t *src,
                 int src_len,
                 int count)
{
    /* 1. NULL-pointer guards */
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
                "safe_memcopy: count (%d) must not be negative\n",
                count);
        return -1;
    }
    /* 3. Destination-overflow check */
    if (count > DEST_SIZE) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds dest size (%d)\n",
                count, DEST_SIZE);
        return -1;
    }
    /* 4. Source over-read check */
    if (src_len < 0 || count > src_len) {
        fprintf(stderr,
                "safe_memcopy: count (%d) exceeds src length (%d)\n",
                count, src_len);
        return -1;
    }
    /* 5. All guards passed — safe to copy */
    memcpy(dest, src, (size_t)count);
    return 0;   /* success */
}