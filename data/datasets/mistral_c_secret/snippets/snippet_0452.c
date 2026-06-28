#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "db_password_123"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
} DbConnector;

DbConnector* create_db_connector(const char *host, int port, const char *user) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector);
}

void connect_to_db(DbConnector *connector) {
    printf("Connecting to database at %s:%d with user %s and password %s\n",
           connector->host, connector->port, connector->user, connector->password);
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "db_user");
    connect_to_db(connector);
    destroy_db_connector(connector);
    return 0;
}