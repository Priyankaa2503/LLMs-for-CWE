// C (stdio FILE* streams)
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERNAME_LEN 64
#define MAX_LINE_LEN 2048

static int is_allowed_username_char(unsigned char c) {
  return (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9') ||
         c == '_' || c == '-';
}

static void write_http_response(FILE *response, int status, const char *reason, const char *body) {
  if (!response) return;
  size_t body_len = body ? strlen(body) : 0;

  fprintf(response, "HTTP/1.1 %d %s\r\n", status, reason);
  fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
  fprintf(response, "X-Content-Type-Options: nosniff\r\n");
  fprintf(response, "Content-Length: %zu\r\n", body_len);
  fprintf(response, "Connection: close\r\n");
  fprintf(response, "\r\n");
  if (body_len) fwrite(body, 1, body_len, response);
  fflush(response);
}

static int parse_username(const char *req, char *out, size_t out_sz) {
  if (!req || !out || out_sz == 0) return 0;

  // Look for "username=" anywhere in the request (querystring or body).
  const char *p = strstr(req, "username=");
  if (!p) return 0;
  p += strlen("username=");

  // Copy until delimiter (&, space, CR, LF) or end.
  size_t n = 0;
  while (*p && *p != '&' && *p != ' ' && *p != '\r' && *p != '\n') {
    if (n + 1 >= out_sz) return 0; // too long
    unsigned char c = (unsigned char)*p;

    // Reject percent-encoding and '+' to keep it strict/safe.
    if (c == '%' || c == '+') return 0;

    if (!is_allowed_username_char(c)) return 0;
    out[n++] = (char)c;
    p++;
  }
  out[n] = '\0';
  return (n > 0 && n <= MAX_USERNAME_LEN);
}

void http_hello_page(FILE *request, FILE *response) {
  if (!request || !response) return;

  char buf[MAX_LINE_LEN];
  char username[MAX_USERNAME_LEN + 1];
  username[0] = '\0';

  // Read up to MAX_LINE_LEN-1 bytes total (best effort).
  size_t total = 0;
  char req_all[MAX_LINE_LEN];
  req_all[0] = '\0';

  while (fgets(buf, sizeof(buf), request)) {
    size_t len = strnlen(buf, sizeof(buf));
    if (total + len >= sizeof(req_all)) break;
    memcpy(req_all + total, buf, len);
    total += len;
    req_all[total] = '\0';

    // Stop early after blank line + some body chars, or if request is small.
    if (strstr(req_all, "\r\n\r\n") || strstr(req_all, "\n\n")) {
      // Continue reading a bit of body if present in the same fgets already; otherwise break.
      // Keep it simple: break once headers end is seen.
      break;
    }
  }

  if (!parse_username(req_all, username, sizeof(username))) {
    write_http_response(response, 400, "Bad Request", "Bad Request\n");
    return;
  }

  char body[128];
  int written = snprintf(body, sizeof(body), "Hello %s\n", username);
  if (written < 0 || (size_t)written >= sizeof(body)) {
    write_http_response(response, 400, "Bad Request", "Bad Request\n");
    return;
  }

  write_http_response(response, 200, "OK", body);
}