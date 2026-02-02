#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p105.c - secret.txt with restrictive permissions */
int main(void) {
    int fd = open("secret.txt", O_CREAT | O_WRONLY, 0600);
    if (fd >= 0) {
        write(fd, "U2FsdGVkX1/R+WzJcxgvX/Iw==", 28);
        close(fd);
        printf("Secret file created\n");
    }
    return 0;
}
