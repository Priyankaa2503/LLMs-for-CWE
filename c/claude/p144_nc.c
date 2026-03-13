#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sqlite3.h>
#include <signal.h>
#include <sys/prctl.h>

#define DB_PATH "/path/to/database.db"
#define PHP_SCRIPT "/path/to/unsubscribe.php"
#define TIMEOUT_SECONDS 5
#define MAX_EMAIL_LEN 254

typedef struct {
    int timed_out;
} TimeoutContext;

static TimeoutContext timeout_context = {0};

void timeout_handler(int sig) {
    timeout_context.timed_out = 1;
}

char* validate_email(const char* email) {
    if (!email || strlen(email) > MAX_EMAIL_LEN) {
        return NULL;
    }

    char* normalized = malloc(strlen(email) + 1);
    if (!normalized) return NULL;

    strcpy(normalized, email);
    for (int i = 0; i < strlen(normalized); i++) {
        normalized[i] = tolower((unsigned char)normalized[i]);
    }

    regex_t regex;
    int ret = regcomp(&regex, 
        "^[a-zA-Z0-9._%+\\-]+@[a-zA-Z0-9.\\-]+\\.[a-zA-Z]{2,}$", 
        REG_EXTENDED);
    
    if (ret != 0) {
        free(normalized);
        return NULL;
    }

    ret = regexec(&regex, normalized, 0, NULL, 0);
    regfree(&regex);

    if (ret != 0) {
        free(normalized);
        return NULL;
    }

    return normalized;
}

int check_and_unsubscribe(const char* email) {
    char* normalized_email = validate_email(email);
    if (!normalized_email) {
        return 0;
    }

    sqlite3* db;
    sqlite3_stmt* stmt;
    int result = 0;

    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
        free(normalized_email);
        sqlite3_close(db);
        return 0;
    }

    const char* query = "SELECT 1 FROM users WHERE email = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        free(normalized_email);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, normalized_email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(normalized_email);
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    pid_t pid = fork();
    if (pid == -1) {
        free(normalized_email);
        return 0;
    }

    if (pid == 0) {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        execl("/usr/bin/php", "php", PHP_SCRIPT, normalized_email, (char*)NULL);
        exit(127);
    }

    int status;
    timeout_context.timed_out = 0;
    signal(SIGALRM, timeout_handler);
    alarm(TIMEOUT_SECONDS);

    if (waitpid(pid, &status, 0) == -1) {
        alarm(0);
        free(normalized_email);
        return 0;
    }

    alarm(0);

    if (timeout_context.timed_out) {
        kill(pid, SIGKILL);
        free(normalized_email);
        return 0;
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        free(normalized_email);
        return 0;
    }

    free(normalized_email);
    return 1;
}

int main() {
    printf("%d\n", check_and_unsubscribe("user@example.com"));
    return 0;
}