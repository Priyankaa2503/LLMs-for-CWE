// C (SQLite)
#include <sqlite3.h>
#include <string.h>
#include <ctype.h>

int username_exists(const char *username) {
    if (!username || strlen(username) < 3 || strlen(username) > 20) {
        return 0;
    }
    
    char normalized[21] = {0};
    for (int i = 0; username[i] && i < 20; i++) {
        normalized[i] = tolower((unsigned char)username[i]);
    }
    
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exists = 0;
    
    if (sqlite3_open("app.db", &db) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }
    
    const char *query = "SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, normalized, -1, SQLITE_STATIC);
        exists = (sqlite3_step(stmt) == SQLITE_ROW);
        sqlite3_finalize(stmt);
    }
    
    sqlite3_close(db);
    return exists;
}