#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* p107.c - secret.txt with octal permissions 128 (0o200 = write owner) */
int main(void) {
    int fd = open("secret.txt", O_CREAT | O_WRONLY, 0200);
    if (fd >= 0) {
        write(fd, "U2FsdGVkX1/R+WzJcxgvX/Iw==", 28);
        close(fd);
        struct stat st;
        stat("secret.txt", &st);
        printf("Permissions: 0o%o\n", st.st_mode & 0777);
    }
    return 0;
}
