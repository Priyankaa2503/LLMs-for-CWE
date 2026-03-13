// C (using libmicrohttpd for HTTP server)
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CORRECT_USERNAME "admin"
#define CORRECT_PASSWORD "secret123"
#define MAX_ATTEMPTS 5
#define TIME_WINDOW 60

typedef struct {
    char ip[INET_ADDRSTRLEN];
    time_t times[MAX_ATTEMPTS];
    int count;
} RateLimit;

RateLimit rate_limits[100];
int rate_limit_count = 0;

// Constant-time string comparison
int constant_time_strcmp(const char *a, const char *b) {
    int result = 0;
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t len = (len_a > len_b) ? len_a : len_b;
    
    for (size_t i = 0; i < len; i++) {
        result |= (i < len_a ? a[i] : 0) ^ (i < len_b ? b[i] : 0);
    }
    
    return result;
}

// Rate limiting check
int check_rate_limit(const char *ip) {
    time_t now = time(NULL);
    
    for (int i = 0; i < rate_limit_count; i++) {
        if (strcmp(rate_limits[i].ip, ip) == 0) {
            // Remove old entries
            int valid_count = 0;
            for (int j = 0; j < rate_limits[i].count; j++) {
                if (now - rate_limits[i].times[j] < TIME_WINDOW) {
                    rate_limits[i].times[valid_count++] = rate_limits[i].times[j];
                }
            }
            rate_limits[i].count = valid_count;
            
            if (rate_limits[i].count >= MAX_ATTEMPTS) {
                return 0;
            }
            
            rate_limits[i].times[rate_limits[i].count++] = now;
            return 1;
        }
    }
    
    // New IP
    if (rate_limit_count < 100) {
        strncpy(rate_limits[rate_limit_count].ip, ip, INET_ADDRSTRLEN - 1);
        rate_limits[rate_limit_count].times[0] = now;
        rate_limits[rate_limit_count].count = 1;
        rate_limit_count++;
        return 1;
    }
    
    return 0;
}

static enum MHD_Result answer_to_connection(void *cls,
                                           struct MHD_Connection *connection,
                                           const char *url,
                                           const char *method,
                                           const char *version,
                                           const char *upload_data,
                                           size_t *upload_data_size,
                                           void **con_cls) {
    if (strcmp(url, "/check_mod") != 0)
        return MHD_NO;
    
    const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    const char *password = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "password");
    const char *remote_ip = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS)->client_addr->sin_addr.s_addr ? "127.0.0.1" : "0.0.0.0";
    
    // SECURITY: In production, use POST+HTTPS instead of GET with credentials in URL
    
    if (!username) username = "";
    if (!password) password = "";
    
    // Rate limiting
    if (!check_rate_limit(remote_ip)) {
        return MHD_HTTP_TOO_MANY_REQUESTS;
    }
    
    // Constant-time comparison
    int username_match = !constant_time_strcmp(username, CORRECT_USERNAME);
    int password_match = !constant_time_strcmp(password, CORRECT_PASSWORD);
    
    // Don't leak which field was wrong
    const char *response = (username_match && password_match) ? "true" : "false";
    
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    
    return ret;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_AUTO,
                                                 8080,
                                                 NULL, NULL,
                                                 &answer_to_connection, NULL,
                                                 MHD_OPTION_END);
    if (NULL == daemon) return 1;
    
    printf("Server running on port 8080\n");
    getchar();
    
    MHD_stop_daemon(daemon);
    return 0;
}