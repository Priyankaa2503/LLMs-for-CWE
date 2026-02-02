#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

/* p103.c
   Open/create exclusive with O_EXCL|O_CREAT|O_TRUNC|O_WRONLY and write string.
*/
int main(void) {
    const char *fname = "important_config";
    const char *msg = "important_config";
    int fd = open(fname, O_CREAT | O_EXCL | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd < 0) { perror("open"); return 1; }
    ssize_t w = write(fd, msg, strlen(msg));
    if (w < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    return 0;
}
