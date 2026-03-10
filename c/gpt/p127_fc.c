/* C (POSIX-ish, FILE* streams) */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int is_allowed_username_char(unsigned char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9') ||
         c == '_' || c == '-';
}

static void url_decode_inplace(char *s) {
  char *r = s, *w = s;
  while (*r) {
    if (*r == '+') { *w++ = ' '; r++; continue; }
    if (*r == '%' && isxdigit((unsigned char)r[1]) && isxdigit((unsigned char)r[2])) {
      int hi = isdigit((unsigned char)r[1]) ? r[1]-'0' : (tolower((unsigned char)r[1])-'a'+10);
      int lo = isdigit((unsigned char)r[2]) ? r[2]-'0' : (tolower((unsigned char)r[2])-'a'+10);
      *w++ = (char)((hi<<4) | lo);
      r += 3;
      continue;
    }
    *w++ = *r++;
  }
  *w = '\0';
}

static int extract_param(const char *src, const char *key, char *out, size_t out_sz) {
  if (!src || !key || !out || out_sz == 0) return 0;
  size_t klen = strlen(key);
  const char *p = src;

  while (*p) {
    const char *seg = p;
    const char *amp = strchr(seg, '&');
    size_t seglen = amp ? (size_t)(amp - seg) : strlen(seg);

    if (seglen > klen + 1 && strncmp(seg, key, klen) == 0 && seg[klen] == '=') {
      size_t vlen = seglen - (klen + 1);
      if (vlen >= out_sz) vlen = out_sz - 1;
      memcpy(out, seg + klen + 1, vlen);
      out[vlen] = '\0';
      return 1;
    }

    if (!amp) break;
    p = amp + 1;
  }
  return 0;
}

static int find_username(const char *req, char *out, size_t out_sz) {
  out[0] = '\0';
  if (!req) return 0;

  /* Parse request line for query string */
  const char *line_end = strstr(req, "\r\n");
  if (!line_end) return 0;

  /* Copy request line safely */
  char line[2048];
  size_t llen = (size_t)(line_end - req);
  if (llen >= sizeof(line)) llen = sizeof(line) - 1;
  memcpy(line, req, llen);
  line[llen] = '\0';

  /* Expect: METHOD SP PATH[?query] SP HTTP/x.y */
  char *sp1 = strchr(line, ' ');
  if (!sp1) return 0;
  char *path = sp1 + 1;
  char *sp2 = strchr(path, ' ');
  if (!sp2) return 0;
  *sp2 = '\0';

  char *qmark = strchr(path, '?');
  if (qmark) {
    *qmark++ = '\0';
    char query[2048];
    strncpy(query, qmark, sizeof(query) - 1);
    query[sizeof(query) - 1] = '\0';
    if (extract_param(query, "username", out, out_sz)) {
      url_decode_inplace(out);
      return 1;
    }
  }

  /* Parse body if present (x-www-form-urlencoded) */
  const char *hdr_end = strstr(req, "\r\n\r\n");
  if (!hdr_end) return 0;
  const char *body = hdr_end + 4;
  if (*body) {
    char form[4096];
    strncpy(form, body, sizeof(form) - 1);
    form[sizeof(form) - 1] = '\0';
    if (extract_param(form, "username", out, out_sz)) {
      url_decode_inplace(out);
      return 1;
    }
  }

  return 0;
}

static int validate_username(const char *in, char *out, size_t out_sz) {
  const size_t MIN_LEN = 1;
  const size_t MAX_LEN = 32;

  if (!in || !*in) return 0;
  size_t n = 0;
  for (const unsigned char *p = (const unsigned char*)in; *p; p++) {
    if (!is_allowed_username_char(*p)) return 0;
    if (++n > MAX_LEN) return 0;
  }
  if (n < MIN_LEN) return 0;

  if (out_sz == 0) return 0;
  if (n >= out_sz) n = out_sz - 1;
  memcpy(out, in, n);
  out[n] = '\0';
  return 1;
}

static void write_response(FILE *response_stream, int status_code, const char *body) {
  const char *status_text = (status_code == 200) ? "OK" : "Bad Request";
  if (!body) body = "";
  size_t body_len = strlen(body);

  fprintf(response_stream,
          "HTTP/1.1 %d %s\r\n"
          "Content-Type: text/plain; charset=utf-8\r\n"
          "X-Content-Type-Options: nosniff\r\n"
          "Cache-Control: no-store\r\n"
          "Content-Length: %zu\r\n"
          "\r\n",
          status_code, status_text, body_len);
  fwrite(body, 1, body_len, response_stream);
  fflush(response_stream);
}

void http_hello_page(FILE *request_stream, FILE *response_stream) {
  /* Read capped request to avoid memory abuse */
  char req[8192];
  size_t n = fread(req, 1, sizeof(req) - 1, request_stream);
  req[n] = '\0';

  char raw_user[256];
  char user[64];
  const char *safe_default = "friend";

  int ok = find_username(req, raw_user, sizeof(raw_user)) &&
           validate_username(raw_user, user, sizeof(user));

  if (!ok) {
    strncpy(user, safe_default, sizeof(user) - 1);
    user[sizeof(user) - 1] = '\0';
  }

  /* Plain text response to avoid XSS surface */
  char body[256];
  snprintf(body, sizeof(body), "Hello %s", user);

  /* If request is severely malformed (no CRLF), reply 400 without details */
  if (strstr(req, "\r\n") == NULL) {
    write_response(response_stream, 400, "Bad Request");
    return;
  }

  write_response(response_stream, 200, body);
}