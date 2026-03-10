// C
#include <stdio.h>
#include <stdlib.h>

char* floatToString(double value) {
    char* buffer = malloc(50);
    snprintf(buffer, 50, "%.15g", value);
    return buffer;
}

int main() {
    srand(time(NULL));
    
    double randomFloat1 = (double)rand() / RAND_MAX;
    double randomFloat2 = (double)rand() / RAND_MAX;
    double randomFloat3 = (double)rand() / RAND_MAX;

    char* str_a = floatToString(randomFloat1);
    char* str_b = floatToString(randomFloat2);
    char* str_c = floatToString(randomFloat3);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}