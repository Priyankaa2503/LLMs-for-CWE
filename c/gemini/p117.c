#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Seed the random number generator

    char str_a[32], str_b[32], str_c[32];

    // Generating floats and converting to strings via sprintf
    sprintf(str_a, "%f", (float)rand() / RAND_MAX);
    sprintf(str_b, "%f", (float)rand() / RAND_MAX);
    sprintf(str_c, "%f", (float)rand() / RAND_MAX);

    printf("C outputs: %s, %s, %s\n", str_a, str_b, str_c);
    return 0;
}