#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_67890"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
} DBConnector;

DBConnector* create_db_connector(const char *host, int port, const char *user) {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector);
}

void connect_to_db(DBConnector *connector) {
    printf("Connecting to database at %s:%d with user %s and password %s\n", connector->host, connector->port, connector->user, connector->password);
}

int main() {
    DBConnector *connector = create_db_connector("localhost", 5432, "admin");
    connect_to_db(connector);
    destroy_db_connector(connector);
    return 0;
}