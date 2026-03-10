// C - Using POSIX directory functions (safe alternative to system())
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }
    
    struct dirent *entry;
    char **entries = NULL;
    int count = 0;
    int capacity = 10;
    
    entries = malloc(capacity * sizeof(char*));
    if (!entries) {
        perror("malloc");
        closedir(dir);
        return 1;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(entries, capacity * sizeof(char*));
            if (!temp) {
                perror("realloc");
                closedir(dir);
                free(entries);
                return 1;
            }
            entries = temp;
        }
        entries[count] = malloc(strlen(entry->d_name) + 1);
        if (!entries[count]) {
            perror("malloc");
            closedir(dir);
            return 1;
        }
        strcpy(entries[count], entry->d_name);
        count++;
    }
    
    if (closedir(dir) == -1) {
        perror("closedir");
        return 1;
    }
    
    qsort(entries, count, sizeof(char*), compare_strings);
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i]);
        free(entries[i]);
    }
    free(entries);
    
    return 0;
}