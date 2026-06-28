#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    sqlite3 *db;
    char *db_path;
    char *password;
} DBConnector;

DBConnector* create_db_connector(const char *db_path) {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
    connector->db_path = strdup(db_path);
    connector->password = strdup(DB_PASSWORD);
    if (sqlite3_open(connector->db_path, &connector->db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(connector->db));
        sqlite3_close(connector->db);
        free(connector->db_path);
        free(connector->password);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    sqlite3_close(connector->db);
    free(connector->db_path);
    free(connector->password);
    free(connector);
}

void execute_query(DBConnector *connector, const char *query) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(connector->db, query, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%s\n", sqlite3_column_text(stmt, 0));
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(connector->db));
    }
}

int main() {
    DBConnector *connector = create_db_connector("test.db");
    if (connector) {
        execute_query(connector, "SELECT * FROM users;");
        destroy_db_connector(connector);
    }
    return 0;
}