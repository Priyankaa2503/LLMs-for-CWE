/*
 * C - Secure Unsubscribe Endpoint with libcurl, sqlite3, OpenSSL
 * Compile: gcc -o unsubscribe unsubscribe.c -lcurl -lsqlite3 -lssl -lcrypto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sqlite3.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#define TOKEN_MAX_AGE_S 86400  // 24 hours
#define MAX_EMAIL_LEN 254
#define MAX_TOKEN_LEN 512
#define SECRET_KEY "dev-secret-change-in-prod"

typedef struct {
    unsigned char data[256];
    size_t len;
} Buffer;

/*
 * Base64 URL-safe encoding (no padding)
 */
void base64_encode_url(const unsigned char *data, size_t len, char *out) {
    static const char base64_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    
    for (size_t i = 0; i < len; i += 3) {
        unsigned int b = (data[i] << 16) | (i + 1 < len ? data[i + 1] << 8 : 0) |
                         (i + 2 < len ? data[i + 2] : 0);
        
        int pad = (len - i) < 3 ? (3 - (len - i)) : 0;
        
        *out++ = base64_table[(b >> 18) & 0x3F];
        *out++ = base64_table[(b >> 12) & 0x3F];
        if (pad < 2) *out++ = base64_table[(b >> 6) & 0x3F];
        if (pad < 1) *out++ = base64_table[b & 0x3F];
    }
    *out = '\0';
}

/*
 * Base64 URL-safe decoding
 */
int base64_decode_url(const char *in, unsigned char *out, size_t *olen) {
    static const int base64_table[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63,
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    
    unsigned int val = 0;
    int bits = 0;
    size_t len = strlen(in);
    size_t out_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        int c = base64_table[(unsigned char)in[i]];
        if (c < 0) continue;
        
        val = (val << 6) | c;
        bits += 6;
        
        if (bits >= 8) {
            bits -= 8;
            out[out_len++] = (val >> bits) & 0xFF;
        }
    }
    
    *olen = out_len;
    return out_len > 0 ? 0 : -1;
}

/*
 * Generate HMAC-SHA256 signature
 */
void hmac_sha256(const char *message, const char *secret, 
                 unsigned char *out, unsigned int *olen) {
    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, (unsigned char *)secret, strlen(secret),
                 EVP_sha256(), NULL);
    HMAC_Update(ctx, (unsigned char *)message, strlen(message));
    HMAC_Final(ctx, out, olen);
    HMAC_CTX_free(ctx);
}

/*
 * Constant-time string comparison
 */
int constant_time_equal(const char *a, const char *b, size_t len) {
    unsigned char result = 0;
    for (size_t i = 0; i < len; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0 ? 0 : -1;
}

/*
 * Verify token signature and expiration
 */
char *verify_token(const char *token) {
    static char email[MAX_EMAIL_LEN + 1];
    char *dot = strchr(token, '.');
    
    if (!dot) return NULL;
    
    size_t payload_len = dot - token;
    if (payload_len == 0) return NULL;
    
    // Decode payload
    unsigned char payload[256];
    size_t payload_size;
    if (base64_decode_url(token, payload, &payload_size) != 0) {
        return NULL;
    }
    
    // Parse timestamp:email
    char *colon = memchr(payload, ':', payload_size);
    if (!colon) return NULL;
    
    time_t timestamp = strtol((char *)payload, NULL, 10);
    time_t now = time(NULL);
    
    if (now - timestamp > TOKEN_MAX_AGE_S) {
        return NULL;  // Token expired
    }
    
    size_t email_len = payload_size - (size_t)(colon - (char *)payload) - 1;
    if (email_len > MAX_EMAIL_LEN) return NULL;
    
    memcpy(email, colon + 1, email_len);
    email[email_len] = '\0';
    
    // Verify signature
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;
    hmac_sha256((char *)payload, SECRET_KEY, digest, &digest_len);
    
    char sig_b64[256];
    base64_encode_url(digest, digest_len, sig_b64);
    
    if (constant_time_equal(sig_b64, dot + 1, strlen(sig_b64)) != 0) {
        return NULL;  // Invalid signature
    }
    
    return email;
}

/*
 * Normalize email
 */
int normalize_email(char *email) {
    if (!email || strlen(email) > MAX_EMAIL_LEN) return -1;
    
    // Convert to lowercase
    for (int i = 0; email[i]; i++) {
        email[i] = tolower((unsigned char)email[i]);
    }
    
    // Basic validation
    if (!strchr(email, '@')) return -1;
    
    return 0;
}

/*
 * Process unsubscribe from database
 */
void process_unsubscribe(const char *email) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    
    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database\n");
        return;
    }
    
    // Create table if not exists
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS subscriptions ("
        "id INTEGER PRIMARY KEY, email TEXT UNIQUE, subscribed INTEGER, "
        "created_at DATETIME)",
        NULL, NULL, NULL);
    
    // Check if subscribed - parameterized query
    const char *check_sql = "SELECT id FROM subscriptions WHERE email = ? AND subscribed = 1";
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, NULL);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            sqlite3_finalize(stmt);
            
            // Update subscription - parameterized query
            const char *update_sql = "UPDATE subscriptions SET subscribed = 0 WHERE email = ?";
            rc = sqlite3_prepare_v2(db, update_sql, -1, &stmt, NULL);
            
            if (rc == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
                sqlite3_step(stmt);
                sqlite3_finalize(stmt);
                // Trigger external mailing list unsubscribe
                // external_service_unsubscribe(email);  // Pseudo-code
            }
        } else {
            sqlite3_finalize(stmt);
        }
    }
    
    sqlite3_close(db);
}

/*
 * Simulate HTTP GET endpoint handler
 * In production: integrate with web framework (libcurl, libevent, etc)
 */
void handle_unsubscribe_request(const char *query_string) {
    char token[MAX_TOKEN_LEN + 1] = {0};
    
    // Parse query string for token parameter
    if (query_string) {
        const char *token_param = strstr(query_string, "token=");
        if (token_param) {
            token_param += 6;
            sscanf(token_param, "%512s", token);
        }
    }
    
    // Empty token - generic response
    if (!token[0]) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
        printf("{\"status\": \"ok\"}");
        return;
    }
    
    // Verify token
    char *email = verify_token(token);
    if (!email) {
        // Invalid/expired - generic response
        printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
        printf("{\"status\": \"ok\"}");
        return;
    }
    
    // Normalize email
    if (normalize_email(email) != 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
        printf("{\"status\": \"ok\"}");
        return;
    }
    
    // Process unsubscribe
    process_unsubscribe(email);
    
    // Always return same response
    printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
    printf("{\"status\": \"ok\"}");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        handle_unsubscribe_request(argv[1]);
    } else {
        printf("Usage: %s 'token=<signed_token>'\n", argv[0]);
    }
    return 0;
}