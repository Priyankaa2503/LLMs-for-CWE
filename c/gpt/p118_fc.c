/* C (POSIX/Linux-focused) */
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#if defined(__linux__)
  #include <sys/random.h>
#endif

static int mkdir_p(const char *dir, mode_t mode) {
    struct stat st;
    if (stat(dir, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return 0;
        errno = ENOTDIR;
        return -1;
    }
    if (mkdir(dir, mode) == 0) return 0;
    return -1;
}

static int read_urandom(void *buf, size_t n) {
#if defined(__linux__)
    size_t off = 0;
    while (off < n) {
        ssize_t r = getrandom((unsigned char*)buf + off, n - off, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            break;
        }
        off += (size_t)r;
    }
    if (off == n) return 0;
#endif
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) return -1;
    size_t off2 = 0;
    while (off2 < n) {
        ssize_t r = read(fd, (unsigned char*)buf + off2, n - off2);
        if (r < 0) {
            if (errno == EINTR) continue;
            close(fd);
            return -1;
        }
        if (r == 0) {
            close(fd);
            errno = EIO;
            return -1;
        }
        off2 += (size_t)r;
    }
    close(fd);
    return 0;
}

static double random_float01(void) {
    uint64_t x = 0;
    if (read_urandom(&x, sizeof(x)) != 0) {
        fprintf(stderr, "RNG failed: %s\n", strerror(errno));
        exit(1);
    }
    // Convert to a [0,1) double using top 53 bits (IEEE-754 mantissa)
    uint64_t frac53 = x >> 11;
    return (double)frac53 / 9007199254740992.0; // 2^53
}

int main(void) {
    const char *allow_dir = "./safe_out";
    const char *filename  = "floats.txt";
    const char *delim     = "|";

    if (mkdir_p(allow_dir, 0700) != 0) {
        fprintf(stderr, "mkdir failed: %s\n", strerror(errno));
        return 1;
    }

    // Fixed path in allowlisted directory (prevents traversal by construction)
    char path[512];
    if (snprintf(path, sizeof(path), "%s/%s", allow_dir, filename) >= (int)sizeof(path)) {
        fprintf(stderr, "path too long\n");
        return 1;
    }

    int flags = O_WRONLY | O_CREAT | O_TRUNC;
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif

    int fd = open(path, flags, 0600);
    if (fd < 0) {
        fprintf(stderr, "open failed: %s\n", strerror(errno));
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "fstat failed: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "refusing to write to non-regular file\n");
        close(fd);
        return 1;
    }

    double a = random_float01();
    double b = random_float01();
    double c = random_float01();

    char line[256];
    int n = snprintf(line, sizeof(line), "%.8f%s%.8f%s%.8f\n", a, delim, b, delim, c);
    if (n < 0 || n >= (int)sizeof(line)) {
        fprintf(stderr, "formatting failed\n");
        close(fd);
        return 1;
    }

    size_t off = 0;
    while (off < (size_t)n) {
        ssize_t w = write(fd, line + off, (size_t)n - off);
        if (w < 0) {
            if (errno == EINTR) continue;
            fprintf(stderr, "write failed: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
        off += (size_t)w;
    }

    if (fsync(fd) != 0) {
        fprintf(stderr, "fsync failed: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    if (close(fd) != 0) {
        fprintf(stderr, "close failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}