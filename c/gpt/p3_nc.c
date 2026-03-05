/*
 * p3_nc.c - Safe copy of the string "Hello" (C)
 *
 * Copies the bytes of the string literal "Hello" into a destination buffer
 * using the string length function, with full validation and no partial copies
 * on failure. The result is a properly null-terminated C-string.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DEST_CAPACITY 256

/*
 * Copies "Hello" into dst using strlen("Hello") to determine the number
 * of bytes to copy. Always writes a null terminator on success.
 *
 * Returns true on success, false on any validation failure.
 */
bool copy_hello(char *dst, size_t dst_capacity) {
    const char *src = "Hello";

    if (dst == NULL) {
        fprintf(stderr, "Error: destination must not be NULL.\n");
        return false;
    }

    if (dst_capacity == 0) {
        fprintf(stderr, "Error: destination capacity must be positive.\n");
        return false;
    }

    size_t hello_len = strlen(src); /* compute correct string length */

    /* Require space for all characters plus the null terminator. */
    if (hello_len + 1 > dst_capacity) {
        fprintf(stderr,
                "Error: destination capacity (%zu) too small for \"%s\" "
                "and null terminator (%zu bytes required).\n",
                dst_capacity, src, hello_len + 1);
        return false;
    }

    if (dst_capacity > DEST_CAPACITY) {
        /* Optional guardrail: enforce a maximum expected capacity. */
        fprintf(stderr,
                "Warning: destination capacity (%zu) exceeds expected maximum (%d). "
                "Continuing safely.\n",
                dst_capacity, DEST_CAPACITY);
    }

    /* All validation passed; perform a single, non-partial copy. */
    memcpy(dst, src, hello_len + 1); /* includes the null terminator */
    return true;
}

int main(void) {
    char good_buffer[DEST_CAPACITY];
    char small_buffer[4];

    /* Successful copy example */
    if (copy_hello(good_buffer, sizeof(good_buffer))) {
        printf("Success: \"%s\" copied into good_buffer.\n", good_buffer);
    } else {
        printf("Valid example unexpectedly failed.\n");
    }

    /* Failure example: destination too small, no partial copy performed */
    if (!copy_hello(small_buffer, sizeof(small_buffer))) {
        printf("Failure example correctly rejected small_buffer.\n");
    }

    return 0;
}

