#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * Safely copies `n` bytes from `src` to `dst`.
 * Returns 0 on success, -1 on failure (errno set).
 */
int safe_memcpy(void *dst, size_t dst_capacity, const void *src, size_t n) {
    if (dst == NULL || src == NULL) {
        errno = EINVAL;
        fprintf(stderr, "safe_memcpy: NULL pointer argument\n");
        return -1;
    }
    if (n == 0) return 0; // no-op, not an error
    if (n > dst_capacity) {
        errno = ENOBUFS;
        fprintf(stderr, "safe_memcpy: destination buffer too small "
                "(%zu bytes needed, %zu available)\n", n, dst_capacity);
        return -1;
    }
    memcpy(dst, src, n);
    return 0;
}

/**
 * Safely copies a string from `src` into `dst`,
 * including the null terminator.
 * Returns 0 on success, -1 on failure (errno set).
 */
int safe_strcpy(char *dst, size_t dst_capacity, const char *src) {
    if (dst == NULL || src == NULL) {
        errno = EINVAL;
        fprintf(stderr, "safe_strcpy: NULL pointer argument\n");
        return -1;
    }
    size_t src_len = strnlen(src, dst_capacity); // won't read past dst_capacity
    if (src_len == dst_capacity) {
        // Either src is too long, or has no null terminator within capacity
        errno = ENOBUFS;
        fprintf(stderr, "safe_strcpy: source too long for destination buffer "
                "(capacity: %zu)\n", dst_capacity);
        return -1;
    }
    size_t bytes_to_copy = src_len + 1; // include null terminator
    memcpy(dst, src, bytes_to_copy);
    return 0;
}

int main(void) {
    const char *message = "Hello, World!";
    char buffer[64];

    if (safe_strcpy(buffer, sizeof(buffer), message) != 0) {
        fprintf(stderr, "Copy failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Copied: \"%s\"\n", buffer);

    // Demonstrate overflow protection
    char small[4];
    if (safe_strcpy(small, sizeof(small), message) != 0) {
        fprintf(stderr, "Expected failure caught: %s\n", strerror(errno));
    }

    return EXIT_SUCCESS;
}