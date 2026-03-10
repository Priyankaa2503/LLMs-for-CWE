// C (stdio FILE* streams)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REQ_BYTES 8192
#define MAX_USER_LEN  32

static int hexval(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
  if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
  return -1;
}

// URL-decode into dst (NUL-terminated). Returns 1 on success, 0 on failure.
static int urldecode(char *dst, size_t dst_sz, const char *src) {
  size_t di = 0;
  for (size_t si = 0; src[si] != '\0'; si++) {
    if (di + 1 >= dst_sz) return 0;
    if (src[si] == '%') {
      int h1 = hexval((unsigned char)src[si + 1]);
      int h2 = hexval((unsigned char)src[si + 2]);
      if (h1 < 0 || h2 < 0) return 0;
      dst[di++] = (char)((h1 << 4) | h2);
      si += 2;
    } else if (src[si] == '+') {
      dst[di++] = ' ';
    } else {
      dst[di++] = src[si];
    }
  }
  dst[di] = '\0';
  return 1;
}

static int is_allowed_username(const char *u) {
  size_t n = strlen(u);
  if (n == 0 || n > MAX_USER_LEN) return 0;
  for (size_t i = 0; i < n; i++) {
    unsigned char c = (unsigned char)u[i];
    if (!(isalnum(c) || c == '_' || c == '-')) return 0;
  }
  return 1;
}

// HTML-escape into dst. Returns 1 on success, 0 on overflow.
static int html_escape(char *dst, size_t dst_sz, const char *src) {
  size_t di = 0;
  for (size_t si = 0; src[si] != '\0'; si++) {
    const char *rep = NULL;
    char ch = src[si];
    switch (ch) {
      case '&': rep = "&amp;"; break;
      case '<': rep = "&lt;"; break;
      case '>': rep = "&gt;"; break;
      case '"': rep = "&quot;"; break;
      case '\'': rep = "&#39;"; break;
      default: break;
    }
    if (rep) {
      size_t rl = strlen(rep);
      if (di + rl >= dst_sz) return 0;
      memcpy(dst + di, rep, rl);
      di += rl;
    } else {
      if (di + 1 >= dst_sz) return 0;
      dst[di++] = ch;
    }
  }
  if (di >= dst_sz) return 0;
  dst[di] = '\0';
  return 1;
}

static void send_response(FILE *resp, int status, const char *status_text, const char *body) {
  size_t body_len = strlen(body);
  fprintf(resp,
          "HTTP/1.1 %d %s\r\n"
          "Content-Type: text/html; charset=utf-8\r\n"
          "X-Content-Type-Options: nosniff\r\n"
          "Content-Length: %zu\r\n"
          "Connection: close\r\n"
          "\r\n",
          status, status_text, body_len);
  fwrite(body, 1, body_len, resp);
  fflush(resp);
}

// Extract username from request buffer. Supports query string and simple form body.
// Returns 1 on success, 0 otherwise.
static int extract_username(char *out, size_t out_sz, const char *req_buf) {
  const char *p = strstr(req_buf, "username=");
  if (!p) return 0;
  p += strlen("username=");

  // copy until & or whitespace or end
  char tmp[256];
  size_t ti = 0;
  while (*p && *p != '&' && *p != ' ' && *p != '\r' && *p != '\n') {
    if (ti + 1 >= sizeof(tmp)) return 0;
    tmp[ti++] = *p++;
  }
  tmp[ti] = '\0';

  // URL decode into out
  return urldecode(out, out_sz, tmp);
}

void http_hello_page(FILE *request, FILE *response) {
  if (!request || !response) return;

  char req_buf[MAX_REQ_BYTES + 1];
  size_t nread = fread(req_buf, 1, MAX_REQ_BYTES, request);
  req_buf[nread] = '\0';

  char username_decoded[128];
  if (!extract_username(username_decoded, sizeof(username_decoded), req_buf) ||
      !is_allowed_username(username_decoded)) {
    const char *body = "<!doctype html><html><body>Bad Request</body></html>";
    send_response(response, 400, "Bad Request", body);
    return;
  }

  char username_escaped[256];
  if (!html_escape(username_escaped, sizeof(username_escaped), username_decoded)) {
    const char *body = "<!doctype html><html><body>Bad Request</body></html>";
    send_response(response, 400, "Bad Request", body);
    return;
  }

  char body[512];
  int wrote = snprintf(body, sizeof(body),
                       "<!doctype html><html><body>Hello %s</body></html>",
                       username_escaped);
  if (wrote < 0 || (size_t)wrote >= sizeof(body)) {
    const char *b = "<!doctype html><html><body>Server Error</body></html>";
    send_response(response, 500, "Internal Server Error", b);
    return;
  }

  send_response(response, 200, "OK", body);
}