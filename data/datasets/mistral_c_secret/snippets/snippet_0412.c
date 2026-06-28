#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *database;
} DBConnector;

DBConnector *create_db_connector(const char *host, int port, const char *user, const char *database) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DBConnector *connector = create_db_connector("localhost", 3306, "admin", "test_db");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created with password: %s\n", connector->password);

    destroy_db_connector(connector);
    return 0;
}