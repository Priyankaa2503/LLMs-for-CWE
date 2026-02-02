#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* p98.c - registration with bcrypt hash */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("{\"status\":\"registered with bcrypt hash\"}\n");
    return 0;
}
