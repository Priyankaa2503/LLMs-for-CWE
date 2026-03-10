// C (POSIX): list current directory without system()
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *path = ".";  // not user-controlled
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "opendir('%s') failed: %s\n", path, strerror(errno));
        return 1;
    }

    errno = 0;
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (printf("%s\n", ent->d_name) < 0) {
            fprintf(stderr, "printf failed\n");
            (void)closedir(dir);
            return 1;
        }
        errno = 0;
    }

    if (errno != 0) {
        fprintf(stderr, "readdir failed: %s\n", strerror(errno));
        (void)closedir(dir);
        return 1;
    }

    if (closedir(dir) != 0) {
        fprintf(stderr, "closedir failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}