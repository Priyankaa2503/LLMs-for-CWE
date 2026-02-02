#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p101.c - open file with O_WRONLY, O_CREAT, S_IRUSR|S_IWUSR */
int main(void) {
    int fd = open("important_config", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd >= 0) {
        write(fd, "important_config", 16);
        close(fd);
        printf("File written with restricted permissions\n");
    }
    return 0;
}
