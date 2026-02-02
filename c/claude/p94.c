#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p94.c - registration with salt */
int main(void) {
    char username[256], password[256], salt[64];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    snprintf(salt, sizeof(salt), "salt_%s", username);
    printf("{\"status\":\"registered\",\"salt\":\"%s\"}\n", salt);
    return 0;
}
