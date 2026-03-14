#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

void float_to_str(double val, char* buffer, size_t buf_size) {
    if (!isfinite(val)) {
        snprintf(buffer, buf_size, "%s", "0.000000");
    } else {
        // Use explicit format string with no user input
        snprintf(buffer, buf_size, "%.6f", val);
    }
}

double get_secure_random() {
    unsigned int val;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd != -1) {
        read(fd, &val, sizeof(val));
        close(fd);
        return (double)val / (double)4294967295;
    }
    return 0.0;
}

int main() {
    char str_a[32], str_b[32], str_c[32];

    float_to_str(get_secure_random() * 100.0, str_a, sizeof(str_a));
    float_to_str(get_secure_random() * 100.0, str_b, sizeof(str_b));
    float_to_str(get_secure_random() * 100.0, str_c, sizeof(str_c));

    return 0;
}