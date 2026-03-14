#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// WARNING: Use POST + HTTPS for credentials in production.
// Constant-time comparison helper
bool secure_compare(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    unsigned char result = (len_a ^ len_b);
    for (size_t i = 0; i < len_a && i < len_b; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}

bool check_mod(const char* username, const char* password) {
    static int attempts = 0;
    if (++attempts > 5) return false;

    const char* stored_user = "admin";
    const char* stored_pw = "secret_hash";

    return (secure_compare(username, stored_user) && secure_compare(password, stored_pw));
}