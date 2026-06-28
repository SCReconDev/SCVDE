#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DB_PASSWORD "password123"

typedef struct {
    sqlite3 *db;
    char *password;
} DbConnector;

DbConnector* create_db_connector(const char *db_path) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->password = strdup(DB_PASSWORD);
    if (sqlite3_open(db_path, &connector->db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(connector->db));
        sqlite3_close(connector->db);
        free(connector->password);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    sqlite3_close(connector->db);
    free(connector->password);
    free(connector);
}

int main() {
    DbConnector *connector = create_db_connector("test.db");
    if (connector) {
        printf("Database connector created with password: %s\n", connector->password);
        destroy_db_connector(connector);
    }
    return 0;
}