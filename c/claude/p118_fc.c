// C: Secure random floats to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void write_random_floats() {
    // Fixed output directory
    const char *output_dir = "/tmp/secure_output";
    const char *filename = "random_floats.txt";
    char filepath[256];
    
    // Safely construct path with bounds checking
    if (snprintf(filepath, sizeof(filepath), "%s/%s", output_dir, filename) < 0) {
        fprintf(stderr, "Path construction error\n");
        return;
    }
    
    // Create directory if needed
    mkdir(output_dir, 0700);
    
    // Open /dev/urandom for crypto-secure random
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd < 0) {
        fprintf(stderr, "Cannot open /dev/urandom: %s\n", strerror(errno));
        return;
    }
    
    // Generate 3 random floats
    double floats[3];
    unsigned char bytes[8];
    for (int i = 0; i < 3; i++) {
        if (read(urandom_fd, bytes, 8) != 8) {
            fprintf(stderr, "Read error from /dev/urandom: %s\n", strerror(errno));
            close(urandom_fd);
            return;
        }
        // Convert bytes to float in [0, 1)
        unsigned long val = 0;
        for (int j = 0; j < 8; j++) {
            val = (val << 8) | bytes[j];
        }
        floats[i] = (double)(val % 1000000) / 1000000.0;
    }
    close(urandom_fd);
    
    // Open output file with secure permissions
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        fprintf(stderr, "File error: %s\n", strerror(errno));
        return;
    }
    
    // Write formatted floats with delimiter
    FILE *f = fdopen(fd, "w");
    if (!f) {
        fprintf(stderr, "fdopen error: %s\n", strerror(errno));
        close(fd);
        return;
    }
    
    if (fprintf(f, "%.17g|%.17g|%.17g", floats[0], floats[1], floats[2]) < 0) {
        fprintf(stderr, "Write error: %s\n", strerror(errno));
    } else {
        printf("Success: %.17g|%.17g|%.17g\n", floats[0], floats[1], floats[2]);
    }
    
    if (fclose(f) < 0) {
        fprintf(stderr, "Close error: %s\n", strerror(errno));
    }
}

int main() {
    write_random_floats();
    return 0;
}