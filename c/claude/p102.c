#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p102.c - open file with S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH */
int main(void) {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd >= 0) {
        write(fd, "important_config", 16);
        close(fd);
        printf("File created with group and other read permissions\n");
    }
    return 0;
}
