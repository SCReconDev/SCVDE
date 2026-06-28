#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *host;
    char *user;
    char *password;
    int port;
} DBConnector;

DBConnector *create_db_connector(const char *host, const char *user, int port) {
    DBConnector *connector = malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->user = strdup(user);
    if (connector->user == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->port = port;

    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    if (connector != NULL) {
        if (connector->host != NULL) {
            free(connector->host);
        }
        if (connector->user != NULL) {
            free(connector->user);
        }
        free(connector);
    }
}

int main() {
    DBConnector *connector = create_db_connector("localhost", "admin", 5432);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create DB connector\n");
        return 1;
    }

    printf("DB Connector created with password: %s\n", connector->password);

    destroy_db_connector(connector);
    return 0;
}