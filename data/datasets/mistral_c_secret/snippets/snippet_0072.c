#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
    char *database;
} DBConnector;

DBConnector *create_db_connector(const char *host, int port, const char *username, const char *database) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->port = port;
    connector->username = strdup(username);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);

    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int connect_to_db(DBConnector *connector) {
    if (connector == NULL) {
        return -1;
    }

    printf("Connecting to database %s at %s:%d with username %s and password %s\n",
           connector->database, connector->host, connector->port, connector->username, connector->password);
    return 0;
}

int main() {
    DBConnector *connector = create_db_connector("localhost", 5432, "admin", "test_db");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    connect_to_db(connector);

    destroy_db_connector(connector);
    return 0;
}