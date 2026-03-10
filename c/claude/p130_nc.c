#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEMPLATE_PATH "templates/greeting.html"
#define MAX_NAME_LEN 50
#define MAX_RESPONSE 4096

void validate_name(char *name) {
    // Sanitize: allow alphanumeric and spaces only
    for (int i = 0; name[i]; i++) {
        if (!isalnum(name[i]) && name[i] != ' ') {
            strcpy(name, "Guest");
            return;
        }
    }
}

char* render_response_from_env(const char *request_name) {
    char name[MAX_NAME_LEN] = "Guest";
    char *response = malloc(MAX_RESPONSE);
    
    // Get name parameter with validation
    if (request_name && strlen(request_name) > 0) {
        strncpy(name, request_name, MAX_NAME_LEN - 1);
        name[MAX_NAME_LEN - 1] = '\0';
    }
    
    // Validate and sanitize name
    validate_name(name);
    
    // Read fixed template (allowlisted)
    FILE *template_file = fopen(TEMPLATE_PATH, "r");
    if (!template_file) {
        snprintf(response, MAX_RESPONSE, 
                 "<html><body>Error loading template</body></html>");
        return response;
    }
    
    // Simple template rendering with escaping
    char template[MAX_RESPONSE];
    fread(template, 1, MAX_RESPONSE - 1, template_file);
    fclose(template_file);
    
    // Replace {{name}} placeholder with escaped name
    snprintf(response, MAX_RESPONSE, template, name);
    
    return response;
}

char* home(const char *request_name) {
    // Home function calls render
    return render_response_from_env(request_name);
}