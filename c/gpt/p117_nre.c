// C11 (Linux): uses getrandom() or /dev/urandom for cryptographically secure randomness.
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__linux__)
  #include <sys/random.h>
#endif

static void secure_random_bytes(void *buf, size_t n) {
#if defined(__linux__)
    size_t off = 0;
    while (off < n) {
        ssize_t r = getrandom((unsigned char *)buf + off, n - off, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            break;
        }
        off += (size_t)r;
    }
    if (off == n) return;
#endif
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) { perror("open /dev/urandom"); exit(1); }
    size_t off = 0;
    while (off < n) {
        ssize_t r = read(fd, (unsigned char *)buf + off, n - off);
        if (r < 0) {
            if (errno == EINTR) continue;
            perror("read /dev/urandom");
            close(fd);
            exit(1);
        }
        if (r == 0) { fprintf(stderr, "short read /dev/urandom\n"); close(fd); exit(1); }
        off += (size_t)r;
    }
    close(fd);
}

static double random_double_01(void) {
    // Construct a double in [0,1) from 53 random bits.
    uint64_t v = 0;
    secure_random_bytes(&v, sizeof(v));
    v >>= 11; // keep 53 bits
    double d = (double)v * (1.0 / (double)(UINT64_C(1) << 53));
    if (!isfinite(d)) { fprintf(stderr, "non-finite double\n"); exit(1); }
    return d;
}

static void float_to_str(double x, char *out, size_t out_sz) {
    if (!isfinite(x)) { fprintf(stderr, "non-finite double\n"); exit(1); }
    int n = snprintf(out, out_sz, "%.6f", x); // fixed format string
    if (n < 0 || (size_t)n >= out_sz) { fprintf(stderr, "formatting error\n"); exit(1); }
}

int main(void) {
    double a = random_double_01();
    double b = random_double_01();
    double c = random_double_01();

    char str_a[64], str_b[64], str_c[64];
    float_to_str(a, str_a, sizeof str_a);
    float_to_str(b, str_b, sizeof str_b);
    float_to_str(c, str_c, sizeof str_c);

    // Use variables str_a, str_b, str_c as needed
    return 0;
}