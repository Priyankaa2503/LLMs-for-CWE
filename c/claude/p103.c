#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p103.c - O_EXCL flag prevents overwrite */
int main(void) {
    int fd = open("important_config", O_CREAT | O_EXCL | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd >= 0) {
        write(fd, "important_config", 16);
        close(fd);
        printf("File created exclusively\n");
    } else {
        printf("File already exists\n");
    }
    return 0;
}
