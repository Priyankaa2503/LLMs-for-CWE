// C (POSIX): generate 3 random floats, stringify, concatenate, write to a fixed file with 0600 perms.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifdef _WIN32
  #include <io.h>
  #define chmod _chmod
#else
  #include <sys/stat.h>
#endif

int main(void) {
    const char *path = "./random_floats.txt"; // fixed, not user-controlled

    unsigned seed = (unsigned)time(NULL) ^ (unsigned)(uintptr_t)&seed;
    srand(seed);

    double a = (double)rand() / (double)RAND_MAX;
    double b = (double)rand() / (double)RAND_MAX;
    double c = (double)rand() / (double)RAND_MAX;

    char sa[64], sb[64], sc[64];
    if (snprintf(sa, sizeof(sa), "%.9f", a) < 0 ||
        snprintf(sb, sizeof(sb), "%.9f", b) < 0 ||
        snprintf(sc, sizeof(sc), "%.9f", c) < 0) {
        fprintf(stderr, "snprintf failed\n");
        return 1;
    }

    char out[256];
    int n = snprintf(out, sizeof(out), "%s%s%s", sa, sb, sc);
    if (n < 0 || (size_t)n >= sizeof(out)) {
        fprintf(stderr, "output buffer too small\n");
        return 1;
    }

    FILE *f = fopen(path, "wb");
    if (!f) {
        fprintf(stderr, "fopen(%s) failed: %s\n", path, strerror(errno));
        return 1;
    }

#ifndef _WIN32
    // Best-effort least-privilege: 0600 (owner read/write)
    if (chmod(path, 0600) != 0) {
        fprintf(stderr, "chmod(0600) failed: %s\n", strerror(errno));
        fclose(f);
        return 1;
    }
#endif

    size_t wrote = fwrite(out, 1, (size_t)n, f);
    if (wrote != (size_t)n) {
        fprintf(stderr, "write failed: %s\n", strerror(errno));
        fclose(f);
        return 1;
    }

    if (fclose(f) != 0) {
        fprintf(stderr, "fclose failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}