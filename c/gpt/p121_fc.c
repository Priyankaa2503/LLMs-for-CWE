// C (primary reference) — secure bounded copy + print, with checked returns and correct frees.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static size_t safe_strnlen(const char *s, size_t maxlen) {
    if (!s) return 0;
    size_t n = 0;
    while (n < maxlen && s[n] != '\0') n++;
    return n;
}

int main(void) {
    const char *src = "Memory-copy and print flow (secure).";
    const size_t MAX_SRC_SCAN = 4096;

    // Determine required size safely (bounded scan), include space for NUL.
    size_t src_len = safe_strnlen(src, MAX_SRC_SCAN);
    if (src_len == MAX_SRC_SCAN) {
        // Source is too long or not NUL-terminated within bound.
        fprintf(stderr, "Error: source string too long or unterminated.\n");
        return 1;
    }

    size_t dst_cap = src_len + 1; // +1 for NUL
    char *dst = (char *)malloc(dst_cap);
    if (!dst) {
        fprintf(stderr, "malloc failed: %s\n", strerror(errno));
        return 1;
    }

    // Bounded copy: copy exactly src_len bytes, then set NUL terminator.
    if (src_len > 0) {
        memcpy(dst, src, src_len);
    }
    dst[src_len] = '\0';

    // Print with checked return value (CWE-252)
    if (printf("%s\n", dst) < 0) {
        fprintf(stderr, "printf failed.\n");
        free(dst);
        return 1;
    }

    // Free exactly once, only after last use.
    free(dst);
    dst = NULL;

    return 0;
}