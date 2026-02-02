#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

/* p101.c
   Open/create `important_config`, write the string "important_config"
   with owner read/write permissions (0600).
*/
int main(void) {
    const char *fname = "important_config";
    const char *msg = "important_config";
    int fd = open(fname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) { perror("open"); return 1; }
    ssize_t w = write(fd, msg, strlen(msg));
    if (w < 0) { perror("write"); close(fd); return 1; }
    close(fd);
    return 0;
}
