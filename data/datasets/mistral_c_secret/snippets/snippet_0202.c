#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_67890"

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
} DbConnector;

DbConnector* create_db_connector(const char *host, int port, const char *username) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->port = port;
    connector->username = strdup(username);
    connector->password = strdup(DB_PASSWORD);

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->password);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created for host: %s\n", connector->host);
    destroy_db_connector(connector);

    return 0;
}