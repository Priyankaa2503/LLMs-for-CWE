#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies bytes from msg into dst using strlen(msg) to determine the
 * number of bytes.  Always writes a null terminator.
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_message(char *dst, const char *msg) {
    if (dst == NULL || msg == NULL) {
        fprintf(stderr, "Error: null pointer argument.\n");
        return false;
    }

    size_t msg_len = strlen(msg);

    /* msg_len + null terminator must fit within capacity */
    if (msg_len >= DEST_CAPACITY) {
        fprintf(stderr,
                "Error: message length (%zu) would overflow destination capacity "
                "(%d) after null terminator.\n",
                msg_len, DEST_CAPACITY);
        return false;
    }

    memcpy(dst, msg, msg_len);
    dst[msg_len] = '\0';

    printf("Success: copied %zu byte(s) + null terminator.\n", msg_len);
    return true;
}

int main(void) {
    char dst[DEST_CAPACITY];

    /* Valid call */
    copy_message(dst, "Hello, secure world!");
    printf("dst = \"%s\"\n", dst);

    /* Invalid: message too long */
    char long_msg[DEST_CAPACITY + 1];
    memset(long_msg, 'A', DEST_CAPACITY);
    long_msg[DEST_CAPACITY] = '\0';
    copy_message(dst, long_msg);

    return 0;
}
