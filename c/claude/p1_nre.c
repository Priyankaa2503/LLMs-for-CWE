#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define DEST_BUFFER_SIZE 256

/*
 * safe_copy: copies exactly n bytes from src into dest.
 *
 * Returns  0 on success.
 * Returns -1 if dest or src is NULL.
 * Returns -2 if n is negative.
 * Returns -3 if n exceeds DEST_BUFFER_SIZE (256).
 * Returns -4 if src_len < n (source does not contain n bytes).
 */
int safe_copy(unsigned char *dest, const unsigned char *src, int n, size_t src_len)
{
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "Error: NULL pointer argument.\n");
        return -1;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n is negative (%d).\n", n);
        return -2;
    }

    if (n > DEST_BUFFER_SIZE) {
        fprintf(stderr, "Error: n (%d) exceeds destination buffer size (%d).\n",
                n, DEST_BUFFER_SIZE);
        return -3;
    }

    if ((size_t)n > src_len) {
        fprintf(stderr, "Error: n (%d) exceeds source length (%zu).\n", n, src_len);
        return -4;
    }

    /* memcpy_s is preferred in C11 Annex K; fall back to memcpy when size is validated */
    memcpy(dest, src, (size_t)n);

    printf("Success: copied %d byte(s).\n", n);
    return 0;
}

int main(void)
{
    unsigned char destination[DEST_BUFFER_SIZE];
    const unsigned char source[] = "Hello, secure world!";
    size_t source_len = sizeof(source) - 1; /* exclude null terminator */

    /* Normal copy */
    safe_copy(destination, source, 5, source_len);

    /* n exceeds buffer */
    safe_copy(destination, source, 300, source_len);

    /* n is negative */
    safe_copy(destination, source, -1, source_len);

    /* n exceeds source length */
    safe_copy(destination, source, 100, source_len);

    /* NULL source */
    safe_copy(destination, NULL, 5, source_len);

    return 0;
}
