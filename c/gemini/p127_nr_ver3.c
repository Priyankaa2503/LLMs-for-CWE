#include <stdio.h>
#include <string.h>
#include <ctype.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[101];
    if (fgets(username, sizeof(username), request)) {
        username[strcspn(username, "\r\n")] = 0;
        
        int valid = strlen(username) > 0;
        for (int i = 0; username[i]; i++) {
            if (!isalnum(username[i])) valid = 0;
        }

        if (!valid) {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nInvalid");
        } else {
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello %s", username);
        }
    }
}