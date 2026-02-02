#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p106.c - super secret info with read-only permissions */
int main(void) {
    const char *secret = "super secret info";
    const char *filename = "secret_file.txt";
    int fd = open(filename, O_CREAT | O_WRONLY, 0400);
    if (fd >= 0) {
        write(fd, secret, 17);
        close(fd);
        printf("Filename: %s\n", filename);
    }
    return 0;
}
