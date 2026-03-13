#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <regex.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_EMAIL_LEN 254
#define PHP_BIN "/usr/bin/php"
#define TIMEOUT_SECONDS 5

typedef struct {
    int timeout_triggered;
} TimeoutContext;

static void timeout_handler(int sig) {
    // Signal handler for timeout
}

/**
 * Validate and normalize email (basic RFC validation)
 * Returns 1 if valid, 0 otherwise
 */
static int validate_email(const char *email, char *normalized) {
    if (!email || strlen(email) > MAX_EMAIL_LEN || strlen(email) < 3) {
        return 0;
    }
    
    // Basic regex: [a-zA-Z0-9+._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}
    regex_t regex;
    if (regcomp(&regex, 
        "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$",
        REG_EXTENDED) != 0) {
        return 0;
    }
    
    int valid = regexec(&regex, email, 0, NULL, 0) == 0 ? 1 : 0;
    regfree(&regex);
    
    if (!valid) return 0;
    
    // Normalize to lowercase
    strcpy(normalized, email);
    for (char *p = normalized; *p; p++) {
        *p = tolower((unsigned char)*p);
    }
    
    return 1;
}

/**
 * Securely unsubscribe an email with timeout and safety guarantees.
 * Returns: 1 if PHP script ran successfully,
 *          0 if email not found or execution failed
 */
int unsubscribe_email(const char *email, const char *db_path, 
                      const char *php_script_path) {
    char normalized_email[MAX_EMAIL_LEN + 1];
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    pid_t pid;
    int status;
    int result = 0;
    
    if (!email || !db_path || !php_script_path) {
        return 0;
    }
    
    // Email validation and normalization
    if (!validate_email(email, normalized_email)) {
        return 0;
    }
    
    // Database check with parameterized query
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        return 0;
    }
    
    const char *query = "SELECT id FROM users WHERE email = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }
    
    sqlite3_bind_text(stmt, 1, normalized_email, -1, SQLITE_STATIC);
    
    int email_exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    if (!email_exists) {
        return 0;
    }
    
    // Safe PHP invocation with fork/execve (no shell)
    pid = fork();
    
    if (pid == -1) {
        return 0;  // Fork failed
    }
    
    if (pid == 0) {
        // Child process
        char *argv[] = {
            (char *)PHP_BIN,
            (char *)php_script_path,
            normalized_email,
            NULL
        };
        
        // Change to safe directory
        chdir("/tmp");
        
        // Execute PHP with no shell interpretation
        execve(PHP_BIN, argv, NULL);
        exit(127);  // Execution failed
    } else {
        // Parent process - wait with timeout
        signal(SIGALRM, timeout_handler);
        alarm(TIMEOUT_SECONDS);
        
        if (waitpid(pid, &status, 0) != -1) {
            alarm(0);  // Cancel alarm
            
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                result = 1;
            }
        } else {
            // Timeout or waitpid error
            kill(pid, SIGKILL);
        }
        alarm(0);  // Ensure alarm is canceled
    }
    
    return result;
}