#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
    const char *filename = "secret.txt";
    const char *secret = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) { perror("open"); return 1; }
    if (write(fd, secret, strlen(secret)) < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    // set permissions to owner read-only
    if (chmod(filename, S_IRUSR) != 0) perror("chmod");
    printf("Wrote %s\n", filename);
    return 0;
}
