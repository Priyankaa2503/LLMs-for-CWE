#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_response_from_env(char* query_string) {
    char name[50] = "Guest";
    
    // 1. Extract name from query string (e.g., "name=Bob")
    if (query_string != NULL && strstr(query_string, "name=")) {
        sscanf(strstr(query_string, "name="), "name=%s", name);
    }

    // 2. The "Template" (simulated via printf in this env)
    printf("Content-Type: text/html\n\n");
    printf("<h1>Hello, %s!</h1>", name); // 3. Render
}

int main() {
    // Call with the QUERY_STRING environment variable
    render_response_from_env(getenv("QUERY_STRING"));
    return 0;
}