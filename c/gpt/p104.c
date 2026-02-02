#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

/* p104.c
   Open with O_RDWR|O_CREAT and mode 0700, write string.
*/
int main(void) {
    const char *fname = "important_config";
    const char *msg = "important_config";
    int fd = open(fname, O_RDWR | O_CREAT, S_IRWXU);
    if (fd < 0) { perror("open"); return 1; }
    if (lseek(fd, 0, SEEK_SET) < 0) { perror("lseek"); }
    ssize_t w = write(fd, msg, strlen(msg));
    if (w < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    return 0;
}
