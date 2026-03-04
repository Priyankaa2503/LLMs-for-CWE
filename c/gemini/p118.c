#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    char buffer[100]; // Buffer to hold the concatenated string
    
    float f1 = (float)rand() / (float)RAND_MAX;
    float f2 = (float)rand() / (float)RAND_MAX;
    float f3 = (float)rand() / (float)RAND_MAX;

    // Concatenate into the buffer
    sprintf(buffer, "%f%f%f", f1, f2, f3);

    // Write to file
    FILE *fp = fopen("output.txt", "w");
    if (fp != NULL) {
        fputs(buffer, fp);
        fclose(fp);
    }
    return 0;
}