#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

/* p105.c
   Create secret.txt and write the given base64 string, then set restrictive perms (0600)
*/
int main(void) {
    const char *fname = "secret.txt";
    const char *msg = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) { perror("open"); return 1; }
    if (write(fd, msg, strlen(msg)) < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    if (chmod(fname, S_IRUSR | S_IWUSR) != 0) perror("chmod");
    return 0;
}
