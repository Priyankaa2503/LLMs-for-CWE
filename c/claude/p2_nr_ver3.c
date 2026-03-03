#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * Copies exactly n bytes from src into dst.
 * Returns 0 on success, -1 on failure with errno set.
 */
int safe_memcpy(void *dst, size_t dst_capacity, const void *src, size_t n) {
    if (dst == NULL || src == NULL) {
        errno = EINVAL;
        fprintf(stderr, "safe_memcpy: NULL pointer argument\n");
        return -1;
    }
    if (n == 0) return 0;
    if (n > dst_capacity) {
        errno = ENOBUFS;
        fprintf(stderr, "safe_memcpy: destination too small (%zu needed, %zu available)\n",
                n, dst_capacity);
        return -1;
    }
    memcpy(dst, src, n);
    return 0;
}

/**
 * Safely copies a null-terminated string from src into dst.
 * Uses strnlen to avoid reading past a known bound if src
 * is not properly null-terminated. Copies the terminator too.
 * Returns 0 on success, -1 on failure with errno set.
 */
int safe_strcpy(char *dst, size_t dst_capacity, const char *src) {
    if (dst == NULL || src == NULL) {
        errno = EINVAL;
        fprintf(stderr, "safe_strcpy: NULL pointer argument\n");
        return -1;
    }
    if (dst_capacity == 0) {
        errno = ENOBUFS;
        fprintf(stderr, "safe_strcpy: destination capacity is zero\n");
        return -1;
    }

    /* strnlen reads at most dst_capacity bytes — never overruns src */
    size_t src_len = strnlen(src, dst_capacity);

    if (src_len == dst_capacity) {
        /* src has no null terminator within capacity, or is exactly too long */
        errno = ENOBUFS;
        fprintf(stderr, "safe_strcpy: source too long for destination (capacity: %zu)\n",
                dst_capacity);
        return -1;
    }

    /* +1 to include the null terminator */
    memcpy(dst, src, src_len + 1);
    return 0;
}

/**
 * Top-level helper: copies a message into a fixed-size buffer.
 * Returns 0 on success, -1 on failure.
 */
int copy_message_to_buffer(char *buffer, size_t buffer_size, const char *message) {
    return safe_strcpy(buffer, buffer_size, message);
}

int main(void) {
    const char *message = "Hello, World!";
    char buffer[64];

    if (copy_message_to_buffer(buffer, sizeof(buffer), message) != 0) {
        fprintf(stderr, "Copy failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Copied: \"%s\"\n", buffer);

    /* Demonstrate overflow protection */
    char small[4];
    if (copy_message_to_buffer(small, sizeof(small), message) != 0) {
        fprintf(stderr, "Expected failure caught: %s\n", strerror(errno));
    }

    return EXIT_SUCCESS;
}