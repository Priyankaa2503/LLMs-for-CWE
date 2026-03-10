// C
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    if (closedir(dir) == -1) {
        perror("closedir");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}