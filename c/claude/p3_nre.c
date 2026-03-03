#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define DEST_BUFFER_SIZE 256

/*
 * copy_hello: copies the literal string "Hello" into dest.
 *
 * n is derived from strlen("Hello") = 5.
 * One extra byte is reserved for the null terminator.
 *
 * Returns  0 on success.
 * Returns -1 if dest is NULL.
 * Returns -2 if n exceeds destination capacity (DEST_BUFFER_SIZE - 1).
 */
int copy_hello(char *dest)
{
    const char *source = "Hello";

    if (dest == NULL) {
        fprintf(stderr, "Error: dest is NULL.\n");
        return -1;
    }

    /* source is a string literal — always valid, never NULL */
    size_t n = strlen(source);   /* n = 5 */

    /* Reserve one byte for the null terminator */
    if (n > DEST_BUFFER_SIZE - 1) {
        fprintf(stderr,
                "Error: source length (%zu) exceeds destination capacity (%d).\n",
                n, DEST_BUFFER_SIZE - 1);
        return -2;
    }

    /*
     * strncpy_s (C11 Annex K) always null-terminates and returns non-zero on
     * failure.  Fall back to memcpy + explicit null termination when the runtime
     * does not provide it — safe here because the bounds check has already passed.
     */
#if defined(__STDC_LIB_EXT1__)
    if (strncpy_s(dest, DEST_BUFFER_SIZE, source, n) != 0) {
        fprintf(stderr, "Error: strncpy_s failed.\n");
        return -3;
    }
#else
    memcpy(dest, source, n);
    dest[n] = '\0';
#endif

    printf("Success: copied %zu byte(s) → \"%s\"\n", n, dest);
    return 0;
}

int main(void)
{
    char destination[DEST_BUFFER_SIZE];

    /* Normal copy */
    copy_hello(destination);

    /* NULL destination */
    copy_hello(NULL);

    return 0;
}
