#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REQUEST_SIZE 10000
#define MAX_USERNAME_LENGTH 100
#define MAX_LINE_LENGTH 1024

typedef struct {
    FILE *input;
    FILE *output;
} RequestResponse;

int is_valid_username(const char *username) {
    if (username == NULL || strlen(username) < 1 || strlen(username) > MAX_USERNAME_LENGTH) {
        return 0;
    }
    
    for (int i = 0; username[i] != '\0'; i++) {
        char c = username[i];
        if (!isalnum(c) && c != '_' && c != '-') {
            return 0;
        }
    }
    
    return 1;
}

void escape_html(const char *input, char *output, size_t output_size) {
    size_t out_idx = 0;
    
    for (int i = 0; input[i] != '\0' && out_idx < output_size - 1; i++) {
        const char *replacement = NULL;
        int replacement_len = 0;
        
        switch (input[i]) {
            case '&':
                replacement = "&amp;";
                replacement_len = 5;
                break;
            case '<':
                replacement = "&lt;";
                replacement_len = 4;
                break;
            case '>':
                replacement = "&gt;";
                replacement_len = 4;
                break;
            case '"':
                replacement = "&quot;";
                replacement_len = 6;
                break;
            case '\'':
                replacement = "&#039;";
                replacement_len = 6;
                break;
            default:
                output[out_idx++] = input[i];
                continue;
        }
        
        if (out_idx + replacement_len < output_size) {
            memcpy(&output[out_idx], replacement, replacement_len);
            out_idx += replacement_len;
        }
    }
    
    output[out_idx] = '\0';
}

void url_decode(const char *src, char *dst, size_t dst_size) {
    size_t dst_idx = 0;
    
    for (int i = 0; src[i] != '\0' && dst_idx < dst_size - 1; i++) {
        if (src[i] == '%' && i + 2 < strlen(src)) {
            int hex_val = 0;
            if (sscanf(&src[i + 1], "%2x", &hex_val) == 1) {
                dst[dst_idx++] = (char)hex_val;
                i += 2;
            } else {
                dst[dst_idx++] = src[i];
            }
        } else if (src[i] == '+') {
            dst[dst_idx++] = ' ';
        } else {
            dst[dst_idx++] = src[i];
        }
    }
    
    dst[dst_idx] = '\0';
}

char *extract_username(const char *query_string) {
    if (query_string == NULL || strlen(query_string) == 0) {
        return NULL;
    }
    
    char *query_copy = malloc(strlen(query_string) + 1);
    strcpy(query_copy, query_string);
    
    char *token = strtok(query_copy, "&");
    while (token != NULL) {
        char *equals = strchr(token, '=');
        if (equals != NULL) {
            int key_len = equals - token;
            if (key_len == 8 && strncmp(token, "username", 8) == 0) {
                char *username = malloc(MAX_USERNAME_LENGTH + 1);
                url_decode(equals + 1, username, MAX_USERNAME_LENGTH + 1);
                free(query_copy);
                return username;
            }
        }
        token = strtok(NULL, "&");
    }
    
    free(query_copy);
    return NULL;
}

void send_error_response(FILE *output, int status_code, const char *message) {
    const char *status_text = "Error";
    
    switch (status_code) {
        case 400:
            status_text = "Bad Request";
            break;
        case 413:
            status_text = "Payload Too Large";
            break;
        case 500:
            status_text = "Internal Server Error";
            break;
    }
    
    char body[MAX_LINE_LENGTH];
    snprintf(body, sizeof(body), "Error %d: %s", status_code, message);
    
    fprintf(output, "HTTP/1.1 %d %s\r\n", status_code, status_text);
    fprintf(output, "Content-Type: text/plain; charset=utf-8\r\n");
    fprintf(output, "Content-Length: %lu\r\n", strlen(body));
    fprintf(output, "Connection: close\r\n");
    fprintf(output, "\r\n");
    fprintf(output, "%s", body);
    fflush(output);
}

void send_success_response(FILE *output, const char *escaped_username) {
    char body[MAX_LINE_LENGTH];
    snprintf(body, sizeof(body), "Hello %s", escaped_username);
    
    fprintf(output, "HTTP/1.1 200 OK\r\n");
    fprintf(output, "Content-Type: text/html; charset=utf-8\r\n");
    fprintf(output, "Content-Length: %lu\r\n", strlen(body));
    fprintf(output, "Connection: close\r\n");
    fprintf(output, "\r\n");
    fprintf(output, "%s", body);
    fflush(output);
}

void http_hello_page(FILE *request, FILE *response) {
    char line[MAX_LINE_LENGTH];
    char method[16], path[MAX_LINE_LENGTH];
    int content_length = 0;
    
    // Read request line
    if (fgets(line, sizeof(line), request) == NULL) {
        send_error_response(response, 400, "Empty request");
        return;
    }
    
    if (sscanf(line, "%15s %1023s", method, path) != 2) {
        send_error_response(response, 400, "Invalid request format");
        return;
    }
    
    // Read headers
    while (fgets(line, sizeof(line), request) != NULL) {
        if (strcmp(line, "\r\n") == 0 || strcmp(line, "\n") == 0) {
            break;
        }
        
        if (strncasecmp(line, "Content-Length:", 15) == 0) {
            sscanf(line, "Content-Length: %d", &content_length);
        }
    }
    
    if (content_length > MAX_REQUEST_SIZE) {
        send_error_response(response, 413, "Payload too large");
        return;
    }
    
    char *username = NULL;
    
    // Extract username based on method
    if (strcmp(method, "GET") == 0) {
        char *query = strchr(path, '?');
        if (query != NULL) {
            username = extract_username(query + 1);
        }
    } else if (strcmp(method, "POST") == 0) {
        if (content_length > 0) {
            char *body = malloc(content_length + 1);
            if (fread(body, 1, content_length, request) == content_length) {
                body[content_length] = '\0';
                username = extract_username(body);
            }
            free(body);
        }
    }
    
    // Validate username
    if (username == NULL) {
        send_error_response(response, 400, "Missing username parameter");
        return;
    }
    
    if (!is_valid_username(username)) {
        free(username);
        send_error_response(response, 400, "Invalid username format");
        return;
    }
    
    // Escape HTML and send response
    char escaped_username[MAX_USERNAME_LENGTH * 6 + 1];
    escape_html(username, escaped_username, sizeof(escaped_username));
    
    send_success_response(response, escaped_username);
    
    free(username);
}