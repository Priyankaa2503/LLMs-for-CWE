#include "civetweb.h"
#include <string.h>

static int http_hello_page(struct mg_connection *conn, void *cbdata) {
    char username[1024];
    char outputbuf[2048];

    // 1. Read the request body into username
    int len = mg_read(conn, username, sizeof(username) - 1);
    username[len] = '\0';

    // 2. Construct the response body
    snprintf(outputbuf, sizeof(outputbuf), 
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // 3. Write the response body to the stream
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    mg_write(conn, outputbuf, strlen(outputbuf));

    // 4. Closing is handled when the function returns
    return 1; 
}