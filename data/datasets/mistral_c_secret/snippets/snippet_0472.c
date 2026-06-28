#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "password123"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
} DBConnector;

DBConnector *create_connector(const char *host, int port, const char *user) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    return connector;
}

void destroy_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector);
}

int main() {
    DBConnector *connector = create_connector("localhost", 5432, "admin");
    printf("Connector created with password: %s\n", connector->password);
    destroy_connector(connector);
    return 0;
}