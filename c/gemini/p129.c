#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char* template_path; } Env;

char* render_response_from_env(Env env) {
    // Get name from query string environment variable
    char *query = getenv("QUERY_STRING");
    char name[50] = "Guest";
    if(query) sscanf(query, "name=%s", name);

    // Simulate rendering
    char* response = malloc(100);
    sprintf(response, "<html>Hello, %s!</html>", name);
    return response;
}

void home(Env env) {
    char* response = render_response_from_env(env);
    printf("Content-Type: text/html\n\n%s", response);
    free(response);
}