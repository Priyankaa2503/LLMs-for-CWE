#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* p96.c - registration with random salt generation */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    srand(time(NULL));
    char salt[32]; snprintf(salt, sizeof(salt), "%08x", rand());
    printf("{\"registered\":true,\"salt\":\"%s\"}\n", salt);
    return 0;
}
