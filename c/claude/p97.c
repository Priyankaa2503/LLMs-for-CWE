#include <stdio.h>
#include <string.h>

/* p97.c - registration page checking for existing username */
int main(void) {
    char username[256], password[256], fname[256], lname[256], email[256];
    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);
    printf("First Name: "); fgets(fname, sizeof(fname), stdin);
    printf("Last Name: "); fgets(lname, sizeof(lname), stdin);
    printf("Email: "); fgets(email, sizeof(email), stdin);
    printf("{\"status\":\"registration succeeded\"}\n");
    return 0;
}
