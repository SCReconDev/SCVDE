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
} DbConnector;

DbConnector* create_db_connector(const char *host, int port, const char *user, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

void connect_to_db(DbConnector *connector) {
    printf("Connecting to database: %s:%d with user: %s and password: %s\n",
           connector->host, connector->port, connector->user, connector->password);
}

void destroy_db_connector(DbConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector->database);
    free(connector);
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin", "mydb");
    connect_to_db(connector);
    destroy_db_connector(connector);
    return 0;
}