// C (POSIX): secure-ish RNG via /dev/urandom, fixed safe path "output.txt", mode 0600
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int urandom_u64(uint64_t *out) {
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd < 0) return -1;

    size_t got = 0;
    unsigned char *p = (unsigned char *)out;
    while (got < sizeof(uint64_t)) {
        ssize_t n = read(fd, p + got, sizeof(uint64_t) - got);
        if (n < 0) {
            if (errno == EINTR) continue;
            close(fd);
            return -1;
        }
        if (n == 0) {
            close(fd);
            errno = EIO;
            return -1;
        }
        got += (size_t)n;
    }
    close(fd);
    return 0;
}

static double rand_float01(void) {
    uint64_t x = 0;
    if (urandom_u64(&x) != 0) return 0.0;
    // map to [0,1) using 53 bits for IEEE-754 double mantissa
    x >>= 11;
    return (double)x / (double)(1ULL << 53);
}

int main(void) {
    const char *path = "output.txt";

    double a = rand_float01();
    double b = rand_float01();
    double c = rand_float01();

    char sa[64], sb[64], sc[64];
    if (snprintf(sa, sizeof(sa), "%.17g", a) < 0) return 1;
    if (snprintf(sb, sizeof(sb), "%.17g", b) < 0) return 1;
    if (snprintf(sc, sizeof(sc), "%.17g", c) < 0) return 1;

    char out[256];
    int outlen = snprintf(out, sizeof(out), "%s%s%s", sa, sb, sc);
    if (outlen < 0 || (size_t)outlen >= sizeof(out)) {
        errno = ENOBUFS;
        perror("snprintf");
        return 1;
    }

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    size_t written = 0;
    while (written < (size_t)outlen) {
        ssize_t n = write(fd, out + written, (size_t)outlen - written);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("write");
            close(fd);
            return 1;
        }
        written += (size_t)n;
    }

    if (close(fd) != 0) {
        perror("close");
        return 1;
    }

    return 0;
}