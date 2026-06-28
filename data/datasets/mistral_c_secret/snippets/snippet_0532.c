#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_PATH "/path/to/database.db"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    sqlite3 *db;
    char *password;
} DBConnector;

DBConnector* create_connector() {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        free(connector);
        return NULL;
    }
    if (sqlite3_open(DB_PATH, &connector->db) != SQLITE_OK) {
        fprintf(stderr, "Error: Cannot open database: %s\n", sqlite3_errmsg(connector->db));
        free(connector->password);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_connector(DBConnector *connector) {
    if (connector != NULL) {
        if (connector->db != NULL) {
            sqlite3_close(connector->db);
        }
        free(connector->password);
        free(connector);
    }
}

int execute_query(DBConnector *connector, const char *query) {
    if (connector == NULL || connector->db == NULL || query == NULL) {
        return -1;
    }
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(connector->db, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error: Cannot prepare statement: %s\n", sqlite3_errmsg(connector->db));
        return -1;
    }
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return result;
}

int main() {
    DBConnector *connector = create_connector();
    if (connector == NULL) {
        return EXIT_FAILURE;
    }
    execute_query(connector, "SELECT * FROM users;");
    destroy_connector(connector);
    return EXIT_SUCCESS;
}