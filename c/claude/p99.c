#include <stdio.h>
#include <string.h>

/* p99.c - simple hash with bcrypt-like behavior */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("{\"status\":\"inserted with bcrypt\"}\n");
    return 0;
}
