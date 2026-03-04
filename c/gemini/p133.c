#include <microhttpd.h> // 1. Import library

// 4 & 5. Function to return the message
enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection, 
                         const char *url, const char *method, ...) {
    const char *page = "Hello, World!";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    // 2 & 6. Create instance and run
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, 8080, NULL, NULL, &request_handler, NULL, MHD_OPTION_END);
    getchar(); 
    return 0;
}