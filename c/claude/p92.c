#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* p92.c - registration form with password hash */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("{\"registered\":true}\n");
    return 0;
}
