#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERNAME_LEN 255
#define MAX_REQUEST_LEN 4096

int is_valid_char(char c) {
    return (isalnum(c) || c == '_' || c == '-');
}

void url_decode(char *src, char *dst, size_t dst_len) {
    size_t i = 0;
    unsigned int val;
    
    while (*src && i < dst_len - 1) {
        if (*src == '%' && *(src + 1) && *(src + 2)) {
            sscanf(src + 1, "%2x", &val);
            dst[i++] = (char)val;
            src += 3;
        } else if (*src == '+') {
            dst[i++] = ' ';
            src++;
        } else {
            dst[i++] = *src;
            src++;
        }
    }
    dst[i] = '\0';
}

void validate_username(char *username) {
    char *src = username;
    char *dst = username;
    
    while (*src) {
        if (is_valid_char(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_LEN + 1];
    char username[MAX_USERNAME_LEN + 1];
    char decoded_username[MAX_USERNAME_LEN + 1];
    char response_text[MAX_USERNAME_LEN + 16];
    char *username_start;
    int username_len;
    
    memset(request_buffer, 0, sizeof(request_buffer));
    memset(username, 0, sizeof(username));
    
    // Read request
    if (fgets(request_buffer, MAX_REQUEST_LEN, request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
        fprintf(response, "Connection: close\r\n\r\n");
        fprintf(response, "Malformed request");
        return;
    }
    
    // Parse username parameter
    username_start = strstr(request_buffer, "username=");
    if (username_start) {
        username_start += 9; // skip "username="
        username_len = 0;
        
        // Extract until & or end of string or whitespace
        while (*username_start && *username_start != '&' && 
               *username_start != ' ' && *username_start != '\r' && 
               *username_start != '\n' && username_len < MAX_USERNAME_LEN) {
            username[username_len++] = *username_start;
            username_start++;
        }
        username[username_len] = '\0';
    }
    
    // URL decode
    url_decode(username, decoded_username, sizeof(decoded_username));
    
    // Limit length
    if (strlen(decoded_username) > MAX_USERNAME_LEN) {
        decoded_username[MAX_USERNAME_LEN] = '\0';
    }
    
    // Validate characters
    validate_username(decoded_username);
    
    // Build response
    if (snprintf(response_text, sizeof(response_text), "Hello %s", decoded_username) < 0) {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
        fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
        fprintf(response, "Connection: close\r\n\r\n");
        return;
    }
    
    // Send response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(response_text));
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "%s", response_text);
    fflush(response);
}