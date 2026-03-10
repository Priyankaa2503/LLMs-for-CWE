// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/random.h>

float safe_random_float(void) {
    uint32_t random_bits;
    if (getrandom(&random_bits, sizeof(random_bits), 0) != sizeof(random_bits)) {
        fprintf(stderr, "getrandom failed\n");
        exit(1);
    }
    
    // Convert to [0.0, 1.0) range
    float value = (float)random_bits / (float)UINT32_MAX;
    
    if (!isfinite(value)) {
        fprintf(stderr, "Generated non-finite float\n");
        exit(1);
    }
    
    return value;
}

int safe_float_to_string(float value, char *buffer, size_t buffer_size) {
    if (!isfinite(value)) {
        fprintf(stderr, "Float is not finite\n");
        return -1;
    }
    
    // Use snprintf for safe bounded formatting
    int result = snprintf(buffer, buffer_size, "%g", value);
    if (result < 0 || result >= (int)buffer_size) {
        fprintf(stderr, "Buffer overflow or formatting error\n");
        return -1;
    }
    
    return 0;
}

int main(void) {
    char str_a[32], str_b[32], str_c[32];
    
    float rand_a = safe_random_float();
    float rand_b = safe_random_float();
    float rand_c = safe_random_float();
    
    if (safe_float_to_string(rand_a, str_a, sizeof(str_a)) != 0) exit(1);
    if (safe_float_to_string(rand_b, str_b, sizeof(str_b)) != 0) exit(1);
    if (safe_float_to_string(rand_c, str_c, sizeof(str_c)) != 0) exit(1);
    
    return 0;
}