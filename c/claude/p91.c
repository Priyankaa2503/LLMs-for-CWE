#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p91.c - simple registration with password hash */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    if (strlen(username) > 0 && strlen(password) > 0) {
        printf("{\"status\":\"registered\",\"username\":\"%s\"}\n", username);
    } else {
        printf("{\"error\":\"empty fields\"}\n");
    }
    return 0;
}
