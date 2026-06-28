#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
    char *database;
} DbConnector;

DbConnector *create_db_connector(const char *host, int port, const char *username, const char *database) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->port = port;

    connector->username = strdup(username);
    if (connector->username == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->username);
        free(connector);
        return NULL;
    }

    connector->database = strdup(database);
    if (connector->database == NULL) {
        free(connector->host);
        free(connector->username);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->database);
        free(connector);
    }
}

int main() {
    const char *host = "localhost";
    int port = 5432;
    const char *username = "admin";
    const char *database = "test_db";

    DbConnector *connector = create_db_connector(host, port, username, database);

    if (connector != NULL) {
        printf("Database Connector created successfully.\n");
        destroy_db_connector(connector);
    } else {
        printf("Failed to create Database Connector.\n");
    }

    return 0;
}