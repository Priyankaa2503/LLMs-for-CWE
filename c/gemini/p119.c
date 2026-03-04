#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Seed the generator
    char string1[20], string2[20], string3[20];

    // Generate and format
    sprintf(string1, "%f", (float)rand() / (float)RAND_MAX);
    sprintf(string2, "%f", (float)rand() / (float)RAND_MAX);
    sprintf(string3, "%f", (float)rand() / (float)RAND_MAX);

    printf("Results: %s, %s, %s\n", string1, string2, string3);
    return 0;
}