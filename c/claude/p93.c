#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* p93.c - registration with hashed password insert into database stub */
int main(void) {
    char username[256], password[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', 'hashed');\n", username);
    return 0;
}
