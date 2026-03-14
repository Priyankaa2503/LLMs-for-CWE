#include <stdio.h>
#include <dirent.h>

int main(void) {
    // Using safe directory stream APIs instead of system("ls")
    DIR *d = opendir(".");
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("Error opening directory");
        return 1;
    }
    return 0;
}