#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *dir = "/tmp/secure_storage";
    const char *path = "/tmp/secure_storage/output.txt";
    
    mkdir(dir, 0700);
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) return 1;

    for (int i = 0; i < 3; i++) {
        double r;
        if (getentropy(&r, sizeof(r)) == 0) {
            char buf[32];
            int len = snprintf(buf, sizeof(buf), "%f", r);
            write(fd, buf, len);
        }
    }

    close(fd);
    return 0;
}