#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "password123"

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
} DBConnector;

DBConnector *create_connector(const char *host, int port, const char *username) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->username = strdup(username);
    connector->password = strdup(DB_PASSWORD);
    return connector;
}

void destroy_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->username);
    free(connector->password);
    free(connector);
}

int main() {
    DBConnector *connector = create_connector("localhost", 5432, "user");
    printf("Connector created for host: %s\n", connector->host);
    destroy_connector(connector);
    return 0;
}