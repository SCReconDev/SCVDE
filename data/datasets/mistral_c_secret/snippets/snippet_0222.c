#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
} DBConnector;

DBConnector *create_db_connector(const char *host, int port, const char *username) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }
    connector->host = strdup(host);
    connector->port = port;
    connector->username = strdup(username);
    connector->password = strdup(DB_PASSWORD);
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->username);
        free(connector->password);
        free(connector);
    }
}

int main() {
    DBConnector *connector = create_db_connector("localhost", 5432, "admin");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create DB connector\n");
        return EXIT_FAILURE;
    }

    printf("DB Connector created with password: %s\n", connector->password);

    destroy_db_connector(connector);
    return EXIT_SUCCESS;
}