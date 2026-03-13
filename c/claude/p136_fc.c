#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* ⚠️ WARNING: Query parameters containing credentials are transmitted in plaintext in URLs.
   This endpoint MUST only be used over HTTPS. Credentials should be sent via POST body or secure headers in production. */

#define STORED_USERNAME "admin"
#define STORED_PASSWORD "secure_password_hash_or_key"
#define MAX_REQUESTS_PER_MINUTE 5

typedef struct {
    char ip[INET_ADDRSTRLEN];
    time_t first_request;
    int request_count;
} RateLimitEntry;

RateLimitEntry rate_limits[256];
int rate_limit_count = 0;

/* Constant-time string comparison to prevent timing attacks */
int timing_safe_equal(const char *a, const char *b) {
    int result = 0;
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    
    if (len_a != len_b) {
        return 0;
    }
    
    for (size_t i = 0; i < len_a; i++) {
        result |= (a[i] ^ b[i]);
    }
    
    return result == 0;
}

/* Check and enforce rate limiting */
int check_rate_limit(const char *ip) {
    time_t now = time(NULL);
    
    for (int i = 0; i < rate_limit_count; i++) {
        if (strcmp(rate_limits[i].ip, ip) == 0) {
            if (now - rate_limits[i].first_request >= 60) {
                rate_limits[i].first_request = now;
                rate_limits[i].request_count = 1;
                return 1;
            }
            
            if (rate_limits[i].request_count >= MAX_REQUESTS_PER_MINUTE) {
                return 0;
            }
            
            rate_limits[i].request_count++;
            return 1;
        }
    }
    
    /* New IP address */
    if (rate_limit_count < 256) {
        strcpy(rate_limits[rate_limit_count].ip, ip);
        rate_limits[rate_limit_count].first_request = now;
        rate_limits[rate_limit_count].request_count = 1;
        rate_limit_count++;
        return 1;
    }
    
    return 0;
}

void check_mod_handler(struct evhttp_request *req, void *arg) {
    struct evkeyvalq params;
    const char *username = NULL;
    const char *password = NULL;
    const char *uri = evhttp_request_get_uri(req);
    struct evhttp_connection *conn = evhttp_request_get_connection(req);
    const char *client_ip = evhttp_connection_get_peer(conn, NULL, NULL);
    
    evhttp_parse_query_str(uri, &params);
    
    username = evhttp_find_header(&params, "username");
    password = evhttp_find_header(&params, "password");
    
    if (!username) username = "";
    if (!password) password = "";
    
    /* Check rate limit */
    if (!check_rate_limit(client_ip)) {
        evhttp_send_reply(req, HTTP_OK, "OK", NULL);
        evbuffer_add(evhttp_request_get_output_buffer(req), "false", 5);
        evhttp_send_reply_end(req);
        return;
    }
    
    /* Constant-time comparison prevents timing attacks */
    int username_match = timing_safe_equal(username, STORED_USERNAME);
    int password_match = timing_safe_equal(password, STORED_PASSWORD);
    
    /* Both must match; no partial success disclosure */
    if (username_match && password_match) {
        evbuffer_add(evhttp_request_get_output_buffer(req), "true", 4);
    } else {
        evbuffer_add(evhttp_request_get_output_buffer(req), "false", 5);
    }
    
    evhttp_send_reply(req, HTTP_OK, "OK", NULL);
}

int main() {
    struct event_base *base = event_base_new();
    struct evhttp *http = evhttp_new(base);
    
    evhttp_set_cb(http, "/check_mod", check_mod_handler, NULL);
    evhttp_bind_socket(http, "0.0.0.0", 8080);
    
    printf("Server running on https://0.0.0.0:8080 (HTTPS required in production)\n");
    event_base_dispatch(base);
    
    return 0;
}