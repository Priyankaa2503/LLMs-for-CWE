#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p104.c - 0700 permissions (rwx owner only) */
int main(void) {
    int fd = open("important_config", O_RDWR | O_CREAT, 0700);
    if (fd >= 0) {
        write(fd, "important_config", 16);
        close(fd);
        printf("File created with 0700 permissions\n");
    }
    return 0;
}
