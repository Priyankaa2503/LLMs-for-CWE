#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define DEST_CAPACITY 256

/* Returns 0 on success, -1 on validation failure */
int safe_copy(uint8_t *dest, const uint8_t *src, size_t n, size_t src_len) {
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (n > DEST_CAPACITY) {
        return -1;
    }
    /* size_t cannot be negative, but guard zero/upper bounds explicitly */
    if (src_len < n) {
        return -1;
    }

    memmove(dest, src, n);
    return 0;
}
