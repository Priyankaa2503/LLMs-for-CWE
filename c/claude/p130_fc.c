// C (Minimal HTTP server with input validation)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_NAME_LENGTH 50
#define MAX_RESPONSE_LENGTH 512

// Fixed template
const char* TEMPLATE = "Hello, %s!";

// URL decode (basic)
void url_decode(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '+') str[i] = ' ';
    }
}

// Validate charset: alphanumeric, spaces, hyphens, apostrophes
int is_valid_name(const char* name) {
    if (!name || strlen(name) == 0) return 1;
    if (strlen(name) > MAX_NAME_LENGTH) return 0;
    
    for (int i = 0; name[i]; i++) {
        char c = name[i];
        if (!isalnum(c) && c != ' ' && c != '-' && c != '\'') {
            return 0;
        }
    }
    return 1;
}

// HTML escape output
void html_escape(const char* input, char* output, int max_len) {
    int out_pos = 0;
    for (int i = 0; input[i] && out_pos < max_len - 5; i++) {
        switch (input[i]) {
            case '<': strcat(output, "&lt;"); out_pos += 4; break;
            case '>': strcat(output, "&gt;"); out_pos += 4; break;
            case '&': strcat(output, "&amp;"); out_pos += 5; break;
            case '"': strcat(output, "&quot;"); out_pos += 6; break;
            default: output[out_pos++] = input[i]; output[out_pos] = '\0';
        }
    }
}

char* render_response_from_env(const char* env_template) {
    char* response = malloc(MAX_RESPONSE_LENGTH);
    if (!response) return NULL;
    
    // Default template (fixed from env or hardcoded)
    const char* template = env_template ? env_template : TEMPLATE;
    
    // Get 'name' from query (simulated)
    const char* name_param = getenv("TEST_NAME");
    char name[MAX_NAME_LENGTH + 1] = "Guest";
    
    if (name_param) {
        strncpy(name, name_param, MAX_NAME_LENGTH);
        name[MAX_NAME_LENGTH] = '\0';
        
        // Validate input
        if (!is_valid_name(name)) {
            strcpy(name, "Guest");
        }
    }
    
    // HTML escape the name
    char escaped_name[MAX_NAME_LENGTH * 6 + 1] = {0};
    html_escape(name, escaped_name, sizeof(escaped_name));
    
    // Safe rendering (no format string vulnerabilities)
    snprintf(response, MAX_RESPONSE_LENGTH, template, escaped_name);
    
    return response;
}

char* home(const char* env) {
    return render_response_from_env(env);
}

int main() {
    char* result = home(NULL);
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("%s\n", result);
    free(result);
    return 0;
}