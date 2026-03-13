#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <regex.h>
#include <ctype.h>

#define MAX_USERNAME 50
#define MAX_STOCK_NAME 10
#define MAX_QUANTITY_STR 20

int validate_stock_name(const char *stock_name) {
    if (!stock_name || strlen(stock_name) == 0 || strlen(stock_name) > MAX_STOCK_NAME) {
        return 0;
    }
    regex_t regex;
    int ret = regcomp(&regex, "^[A-Z0-9-]{1,10}$", REG_EXTENDED);
    if (ret) return 0;
    ret = regexec(&regex, stock_name, 0, NULL, 0);
    regfree(&regex);
    return (ret == 0) ? 1 : 0;
}

int validate_quantity(const char *quantity_str) {
    if (!quantity_str || strlen(quantity_str) == 0 || strlen(quantity_str) > MAX_QUANTITY_STR) {
        return 0;
    }
    for (int i = 0; quantity_str[i]; i++) {
        if (!isdigit(quantity_str[i])) return 0;
    }
    long quantity = strtol(quantity_str, NULL, 10);
    return quantity > 0;
}

int buy_stock(const char *username, const char *stock_name, const char *stock_quantity) {
    // Verify username from authenticated session
    if (!username || strlen(username) == 0 || strlen(username) > MAX_USERNAME) {
        fprintf(stderr, "Invalid username\n");
        return 0;
    }
    
    if (!validate_stock_name(stock_name)) {
        fprintf(stderr, "Invalid stock name\n");
        return 0;
    }
    
    if (!validate_quantity(stock_quantity)) {
        fprintf(stderr, "Invalid quantity\n");
        return 0;
    }
    
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    
    // Prepare parameterized query
    const char *sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    
    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, atoi(stock_quantity));
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    // Caller redirects to /profile
    return 1;
}