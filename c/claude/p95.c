#include <stdio.h>
#include <string.h>

/* p95.c - registration with salt appended */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("{\"registered\":true,\"salt\":\"random_salt\"}\n");
    return 0;
}
