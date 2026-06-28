#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "test.db"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    sqlite3 *db;
    char *password;
} DbConnector;

DbConnector* create_db_connector(const char *db_name) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    if (sqlite3_open(db_name, &connector->db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(connector->db));
        free(connector);
        return NULL;
    }

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Database password not found in environment variables.\n");
        sqlite3_close(connector->db);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        if (connector->db != NULL) {
            sqlite3_close(connector->db);
        }
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector(DB_NAME);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    printf("Database Connector created successfully.\n");
    printf("Password: %s\n", connector->password);

    destroy_db_connector(connector);
    return 0;
}