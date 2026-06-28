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

DbConnector* create_db_connector(const char *host, int port, const char *username, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
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

    char *password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Database password not found in environment variables\n");
        free(connector->host);
        free(connector->username);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->username);
        free(connector);
        return NULL;
    }

    connector->database = strdup(database);
    if (connector->database == NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->password);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin", "mydb");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created with host: %s\n", connector->host);
    printf("Port: %d\n", connector->port);
    printf("Username: %s\n", connector->username);
    printf("Password: %s\n", connector->password);
    printf("Database: %s\n", connector->database);

    destroy_db_connector(connector);
    return 0;
}