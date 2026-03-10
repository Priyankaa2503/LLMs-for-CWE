#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file = NULL;
    char buffer[256] = {0};
    int offset = 0;
    
    srand(time(NULL));
    
    for (int i = 0; i < 3; i++) {
        double random_float = (double)rand() / RAND_MAX;
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%f", random_float);
        if (offset >= (int)sizeof(buffer)) {
            fprintf(stderr, "Error: Buffer overflow\n");
            return 1;
        }
    }
    
    file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open output.txt for writing\n");
        return 1;
    }
    
    if (fprintf(file, "%s", buffer) < 0) {
        fprintf(stderr, "Error: Failed to write to file\n");
        fclose(file);
        return 1;
    }
    
    if (fclose(file) != 0) {
        fprintf(stderr, "Error: Failed to close file\n");
        return 1;
    }
    
    printf("Success: String written to output.txt\n");
    return 0;
}