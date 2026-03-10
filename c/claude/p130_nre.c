// C (simple approach with string validation)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NAME_LEN 100
#define TEMPLATE_FILE "home.html"

int is_valid_name(const char *name) {
    if (!name || strlen(name) == 0 || strlen(name) > MAX_NAME_LEN) {
        return 0;
    }
    for (int i = 0; name[i]; i++) {
        char c = name[i];
        if (!isalnum(c) && c != '_' && c != '-' && c != ' ') {
            return 0;
        }
    }
    return 1;
}

char* render_response_from_env(const char *name) {
    if (!is_valid_name(name)) {
        name = "Guest";
    }
    
    FILE *fp = fopen(TEMPLATE_FILE, "r");
    if (!fp) {
        return NULL;
    }
    
    char buffer[4096] = {0};
    char result[8192] = {0};
    
    while (fgets(buffer, sizeof(buffer), fp)) {
        char *pos = strstr(buffer, "{{name}}");
        if (pos) {
            strncat(result, buffer, pos - buffer);
            strcat(result, name);
            strcat(result, pos + 8);
        } else {
            strcat(result, buffer);
        }
    }
    
    fclose(fp);
    
    char *response = malloc(strlen(result) + 1);
    strcpy(response, result);
    return response;
}

char* home(const char *name) {
    return render_response_from_env(name);
}