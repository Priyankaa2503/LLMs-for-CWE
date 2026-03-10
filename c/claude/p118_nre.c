// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    const char *output_file = "output.txt";
    FILE *fp = NULL;
    char buffer[256];
    int ret;
    
    fp = fopen(output_file, "w");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < 3; i++) {
        double f = (double)random() / RAND_MAX;
        ret = fprintf(fp, "%f", f);
        if (ret < 0) {
            perror("fprintf");
            fclose(fp);
            return EXIT_FAILURE;
        }
    }
    
    if (fclose(fp) != 0) {
        perror("fclose");
        return EXIT_FAILURE;
    }
    
    if (chmod(output_file, S_IRUSR | S_IWUSR) != 0) {
        perror("chmod");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}