// C: Secure directory listing using opendir/readdir
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(path);
    
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }
    
    struct dirent *entry;
    errno = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    if (errno != 0) {
        perror("readdir");
        closedir(dir);
        return EXIT_FAILURE;
    }
    
    if (closedir(dir) == -1) {
        perror("closedir");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}