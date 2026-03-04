#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];

    // Read from the request stream
    if (fgets(username, sizeof(username), request)) {
        // Remove newline if present
        username[strcspn(username, "\n")] = 0;

        // Escape HTML logic (abstracted)
        char *safe_username = escape_html(username);

        // Write to the response stream
        fprintf(response, "hello %s", safe_username);
    }
}