/**
 * p2_fc.c - Safe message copy using string length (C)
 *
 * Copies a NUL-terminated message into a fixed-size 256-byte destination
 * buffer. The number of bytes to copy is computed from strlen(message),
 * leaving room for and setting a terminating '\0'. The function:
 *  - validates non-NULL destination and source
 *  - computes the copy size from the string length safely
 *  - enforces DEST_CAPACITY (256) and reserves space for '\0'
 *  - does not read beyond the source string
 *  - performs no partial copy on failure
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DEST_CAPACITY 256

/**
 * Copies a message into dst using its string length.
 *
 * @param dst      destination buffer; must point to at least DEST_CAPACITY bytes
 * @param dst_size actual size of the destination buffer in bytes
 * @param message  NUL-terminated source string
 * @return true (1) on success, false (0) on validation failure
 */
bool copy_message(char *dst, size_t dst_size, const char *message) {
    if (dst == NULL || message == NULL) {
        fprintf(stderr, "Error: destination and source must not be NULL.\n");
        return false;
    }

    if (dst_size < DEST_CAPACITY) {
        fprintf(stderr,
                "Error: destination buffer must be at least %d bytes (got %zu).\n",
                DEST_CAPACITY, dst_size);
        return false;
    }

    size_t msg_len = strlen(message);

    /* Reserve space for the terminating NUL character. */
    if (msg_len >= DEST_CAPACITY) {
        fprintf(stderr,
                "Error: message length (%zu) does not fit in %d-byte buffer "
                "with space for NUL terminator.\n",
                msg_len, DEST_CAPACITY);
        return false;
    }

    /* All validation passed; perform the copy. */
    for (size_t i = 0; i < msg_len; ++i) {
        dst[i] = message[i];
    }
    dst[msg_len] = '\0';

    return true;
}

int main(void) {
    char dst[DEST_CAPACITY];

    /* Successful case. */
    const char *ok_message = "Short message";
    if (copy_message(dst, sizeof(dst), ok_message)) {
        printf("Success: '%s'\n", dst);
    } else {
        printf("Unexpected failure for valid message.\n");
    }

    /* Failure case: message too long for the buffer. */
    char long_message[300];
    memset(long_message, 'A', sizeof(long_message) - 1);
    long_message[sizeof(long_message) - 1] = '\0';

    if (!copy_message(dst, sizeof(dst), long_message)) {
        printf("Correctly rejected overly long message.\n");
    } else {
        printf("Unexpected success for overly long message.\n");
    }

    return 0;
}

