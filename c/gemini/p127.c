#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];

    // Read username from the request stream
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        username[strcspn(username, "\n")] = 0;
    }

    // Write the formatted string to the response stream
    fprintf(response, "Hello %s", username);
    fflush(response);
}