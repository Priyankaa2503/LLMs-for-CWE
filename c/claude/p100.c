#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

/* p100.c - create file with restricted permissions */
int main(void) {
    int fd = open("important_config", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd >= 0) {
        write(fd, "important_config", 16);
        close(fd);
        printf("File created with restricted permissions\n");
    }
    return 0;
}
