// C (non-crypto RNG via rand)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static void float_to_string(double x, char *out, size_t out_sz) {
    // Explicit, fixed formatting (not user-controlled)
    snprintf(out, out_sz, "%.6f", x);
}

int main(void) {
    srand((unsigned)time(NULL)); // non-crypto seed

    double a = (double)rand() / (double)RAND_MAX;
    double b = (double)rand() / (double)RAND_MAX;
    double c = (double)rand() / (double)RAND_MAX;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) return 1;

    char str_a[32], str_b[32], str_c[32];
    float_to_string(a, str_a, sizeof str_a);
    float_to_string(b, str_b, sizeof str_b);
    float_to_string(c, str_c, sizeof str_c);

    // Example usage (optional): printf("%s %s %s\n", str_a, str_b, str_c);
    (void)str_a; (void)str_b; (void)str_c;
    return 0;
}