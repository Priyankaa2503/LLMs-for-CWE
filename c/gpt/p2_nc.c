/*
 * p2_nc.c - Safe message-to-buffer copy using string length (C)
 *
 * Copies bytes from a source message into a destination buffer, using
 * strlen(message) as the number of bytes to copy. The result is a
 * properly null-terminated C-string on success.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies bytes from msg into dst using strlen(msg) to determine the
 * number of bytes to copy. Always writes a null terminator on success.
 *
 * dst_capacity is the size of dst in bytes.
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_message_to_buffer(char *dst,
                            size_t dst_capacity,
                            const char *msg) {
    if (dst == NULL || msg == NULL) {
        fprintf(stderr, "Error: destination and message must not be NULL.\n");
        return false;
    }

    if (dst_capacity == 0) {
        fprintf(stderr, "Error: destination capacity must be positive.\n");
        return false;
    }

    if (dst_capacity > DEST_CAPACITY) {
        /* Guardrail: this implementation is designed for 256-byte buffers. */
        dst_capacity = DEST_CAPACITY;
    }

    size_t msg_len = strlen(msg); /* derived from the string length */

    /* msg_len is size_t, so it is never negative, but ensure it fits. */
    if (msg_len >= dst_capacity) {
        fprintf(stderr,
                "Error: message length (%zu) would overflow destination capacity "
                "(%zu) after null terminator.\n",
                msg_len, dst_capacity);
        return false;
    }

    /*
     * At this point we know:
     *   - msg_len < dst_capacity
     *   - msg_len + 1 <= dst_capacity (space for null terminator)
     *   - we won't read beyond msg because strlen already computed msg_len.
     */
    memcpy(dst, msg, msg_len);
    dst[msg_len] = '\0';
    return true;
}

int main(void) {
    char dst[DEST_CAPACITY];

    /* Successful copy example */
    if (copy_message_to_buffer(dst, sizeof(dst), "Hello, secure world!")) {
        printf("Success: \"%s\"\n", dst);
    } else {
        printf("Valid example unexpectedly failed.\n");
    }

    /* Failure example: message too long for the destination */
    char long_msg[DEST_CAPACITY + 1];
    memset(long_msg, 'A', sizeof(long_msg) - 1);
    long_msg[sizeof(long_msg) - 1] = '\0';

    if (!copy_message_to_buffer(dst, sizeof(dst), long_msg)) {
        printf("Failure example correctly rejected oversize message.\n");
    }

    return 0;
}

