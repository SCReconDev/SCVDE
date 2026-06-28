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
} DBConnector;

DBConnector* create_db_connector(const char *host, int port, const char *username, const char *database) {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
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
        free(connector->username);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->database = strdup(database);
    if (connector->database == NULL) {
        free(connector->username);
        free(connector->host);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DBConnector *connector) {
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

    DBConnector *connector = create_db_connector(host, port, username, database);

    if (connector == NULL) {
        fprintf(stderr, "Failed to create DB connector\n");
        return 1;
    }

    printf("DB Connector created with host: %s, port: %d, username: %s, database: %s\n",
           connector->host, connector->port, connector->username, connector->database);
    printf("Password: %s\n", connector->password);

    destroy_db_connector(connector);
    return 0;
}