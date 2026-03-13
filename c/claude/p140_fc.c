// C (SQLite3 with prepared statements)
#include <sqlite3.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool validate_username(const char *username) {
    if (!username || strlen(username) < 3 || strlen(username) > 32) {
        return false;
    }
    
    for (int i = 0; username[i]; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            return false;
        }
    }
    return true;
}

bool username_exists(sqlite3 *db, const char *username) {
    // Validate input
    if (!validate_username(username)) {
        return false;
    }
    
    sqlite3_stmt *stmt = NULL;
    const char *query = "SELECT 1 FROM users WHERE username = ? LIMIT 1";
    
    // Prepare parameterized statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        // Log error internally, don't expose to caller
        return false;
    }
    
    // Bind parameter safely
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return false;
    }
    
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    
    return exists;
}