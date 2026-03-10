// C - time-seeded rand (non-cryptographic; document limitation)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

srand(time(NULL));
double float_a = (double)rand() / RAND_MAX * 100;
double float_b = (double)rand() / RAND_MAX * 100;
double float_c = (double)rand() / RAND_MAX * 100;

char str_a[32], str_b[32], str_c[32];
snprintf(str_a, sizeof(str_a), "%.6f", float_a);
snprintf(str_b, sizeof(str_b), "%.6f", float_b);
snprintf(str_c, sizeof(str_c), "%.6f", float_c);