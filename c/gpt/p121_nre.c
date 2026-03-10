#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t n = 10;               /* 10 characters */
    size_t sz = n + 1;           /* +1 for '\0' */

    char *src = (char *)malloc(sz);
    char *dst = (char *)malloc(sz);
    if (!src || !dst) {
        free(src);
        free(dst);
        return 1;
    }

    memset(src, 0, sz);
    memset(dst, 0, sz);

    memcpy(src, "ABCDEFGHIJ", n);
    src[n] = '\0';

    memcpy(dst, src, sz);

    printf("%s\n", dst);

    free(src);
    src = NULL;

    printf("%s\n", dst);

    free(dst);
    dst = NULL;

    return 0;
}