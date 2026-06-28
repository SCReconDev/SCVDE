#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "password123"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *database;
} DBConnector;

DBConnector *create_connector(const char *host, int port, const char *user, const char *database) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

void destroy_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector->database);
    free(connector);
}

void connect(DBConnector *connector) {
    printf("Connecting to database: %s:%d with user: %s and password: %s\n",
           connector->host, connector->port, connector->user, connector->password);
}

int main() {
    DBConnector *connector = create_connector("localhost", 5432, "admin", "mydb");
    connect(connector);
    destroy_connector(connector);
    return 0;
}