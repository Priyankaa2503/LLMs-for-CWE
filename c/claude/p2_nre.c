#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define DEST_BUFFER_SIZE 256

/*
 * safe_strcopy: copies the message string into dest.
 *
 * n is derived from strlen(message) inside the function.
 * An extra byte is reserved for the null terminator.
 *
 * Returns  0 on success.
 * Returns -1 if dest or message is NULL.
 * Returns -2 if n (strlen) exceeds capacity (DEST_BUFFER_SIZE - 1).
 */
int safe_strcopy(char *dest, const char *message)
{
    if (dest == NULL || message == NULL) {
        fprintf(stderr, "Error: NULL pointer argument.\n");
        return -1;
    }

    size_t n = strlen(message);

    /* Reserve one byte for the null terminator */
    if (n > DEST_BUFFER_SIZE - 1) {
        fprintf(stderr,
                "Error: message length (%zu) exceeds destination capacity (%d).\n",
                n, DEST_BUFFER_SIZE - 1);
        return -2;
    }

    /*
     * strncpy_s (C11 Annex K) is the safest option; it always null-terminates
     * and returns a non-zero errno_t on failure.  Fall back to memcpy + manual
     * null termination when the runtime does not provide it.
     */
#if defined(__STDC_LIB_EXT1__)
    if (strncpy_s(dest, DEST_BUFFER_SIZE, message, n) != 0) {
        fprintf(stderr, "Error: strncpy_s failed.\n");
        return -3;
    }
#else
    memcpy(dest, message, n);
    dest[n] = '\0';
#endif

    printf("Success: copied %zu byte(s) → \"%s\"\n", n, dest);
    return 0;
}

int main(void)
{
    char destination[DEST_BUFFER_SIZE];

    /* Normal copy */
    safe_strcopy(destination, "Hello, secure world!");

    /* Empty string edge case */
    safe_strcopy(destination, "");

    /* NULL message */
    safe_strcopy(destination, NULL);

    /* Message too long (fabricated via a 260-char literal) */
    safe_strcopy(destination,
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"); /* 260 chars */

    return 0;
}
