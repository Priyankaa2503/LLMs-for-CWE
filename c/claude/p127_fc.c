#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_REQUEST_SIZE 4096
#define MAX_USERNAME_LENGTH 50
#define DEFAULT_USERNAME "Guest"

typedef struct {
    int status_code;
    const char *status_text;
    const char *username;
} http_response_t;

int is_valid_char(unsigned char c) {
    return isalnum(c) || c == '.' || c == '_' || c == '-';
}

int validate_username(const char *input, char *output) {
    if (!input) {
        strncpy(output, DEFAULT_USERNAME, MAX_USERNAME_LENGTH);
        return 0;
    }
    
    // Skip whitespace
    while (*input && isspace((unsigned char)*input)) {
        input++;
    }
    
    // Check length and characters
    size_t len = 0;
    const char *p = input;
    while (*p && len < MAX_USERNAME_LENGTH) {
        if (!is_valid_char((unsigned char)*p)) {
            strncpy(output, DEFAULT_USERNAME, MAX_USERNAME_LENGTH);
            return -1;
        }
        output[len++] = *p;
        p++;
    }
    
    if (len == 0 || len > MAX_USERNAME_LENGTH) {
        strncpy(output, DEFAULT_USERNAME, MAX_USERNAME_LENGTH);
        return -1;
    }
    
    output[len] = '\0';
    return 0;
}

int extract_username(const char *request_line, char *username) {
    const char *query_start = strchr(request_line, '?');
    if (!query_start) {
        strncpy(username, DEFAULT_USERNAME, MAX_USERNAME_LENGTH);
        return 0;
    }
    
    const char *username_param = strstr(query_start, "username=");
    if (!username_param) {
        strncpy(username, DEFAULT_USERNAME, MAX_USERNAME_LENGTH);
        return 0;
    }
    
    username_param += 9; // strlen("username=")
    
    char temp[MAX_USERNAME_LENGTH + 1];
    int i = 0;
    while (*username_param && *username_param != '&' && *username_param != ' ' && i < MAX_USERNAME_LENGTH) {
        if (*username_param == '%' && *(username_param + 1) && *(username_param + 2)) {
            // Simple URL decode for %20 and common cases
            if (username_param[1] == '2' && username_param[2] == '0') {
                temp[i++] = ' ';
                username_param += 3;
                continue;
            }
        }
        temp[i++] = *username_param;
        username_param++;
    }
    temp[i] = '\0';
    
    return validate_username(temp, username);
}

void send_error_response(int fd, int status_code, const char *status_text) {
    char response[512];
    snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: 0\r\n"
        "Cache-Control: no-store\r\n"
        "Connection: close\r\n"
        "\r\n",
        status_code, status_text);
    
    write(fd, response, strlen(response));
}

void http_hello_page(int request_fd, int response_fd) {
    char request[MAX_REQUEST_SIZE];
    char request_line[512];
    char username[MAX_USERNAME_LENGTH + 1];
    char response[1024];
    ssize_t bytes_read;
    
    // Read request line
    bytes_read = read(request_fd, request, MAX_REQUEST_SIZE - 1);
    if (bytes_read <= 0) {
        send_error_response(response_fd, 400, "Bad Request");
        return;
    }
    
    request[bytes_read] = '\0';
    
    // Extract request line
    char *line_end = strchr(request, '\r');
    if (!line_end) {
        line_end = strchr(request, '\n');
    }
    if (!line_end) {
        send_error_response(response_fd, 400, "Bad Request");
        return;
    }
    
    size_t line_len = line_end - request;
    if (line_len >= sizeof(request_line)) {
        send_error_response(response_fd, 400, "Bad Request");
        return;
    }
    
    strncpy(request_line, request, line_len);
    request_line[line_len] = '\0';
    
    // Validate request line format
    char method[16], path[256], version[16];
    if (sscanf(request_line, "%15s %255s %15s", method, path, version) != 3) {
        send_error_response(response_fd, 400, "Bad Request");
        return;
    }
    
    // Extract and validate username
    if (extract_username(path, username) < 0) {
        // Use default on validation failure
    }
    
    // Build response body
    char body[256];
    snprintf(body, sizeof(body), "Hello %s", username);
    
    // Build HTTP response
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "Cache-Control: no-store\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strlen(body), body);
    
    write(response_fd, response, strlen(response));
}