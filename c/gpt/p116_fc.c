// C (POSIX): list current directory contents using opendir/readdir with checked errors.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

int main(void) {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    errno = 0;
    for (;;) {
        struct dirent *ent = readdir(dir);
        if (ent == NULL) {
            if (errno != 0) {
                perror("readdir");
                (void)closedir(dir);
                return EXIT_FAILURE;
            }
            break; // end of stream
        }

        if (printf("%s\n", ent->d_name) < 0) {
            perror("printf");
            (void)closedir(dir);
            return EXIT_FAILURE;
        }
    }

    if (closedir(dir) != 0) {
        perror("closedir");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}