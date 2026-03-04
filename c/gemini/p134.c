#include <stdio.h>
#include <glib.h> // Using Glib for g_markup_escape_text

void hello(const char* username) {
    // Escaping special characters for HTML safety
    char* safe_username = g_markup_escape_text(username, -1);
    printf("Content-Type: text/plain\n\n");
    printf("Hello %s", safe_username);
    g_free(safe_username);
}

// In C, the "mapping" is usually a series of if-statements 
// or a function pointer table in the main loop.