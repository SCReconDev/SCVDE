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
} DbConnector;

DbConnector* create_db_connector(const char *host, int port, const char *username, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->username = strdup(username);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    free(connector->host);
    free(connector->username);
    free(connector->password);
    free(connector->database);
    free(connector);
}

void connect_to_db(DbConnector *connector) {
    printf("Connecting to database %s at %s:%d with user %s and password %s\n",
           connector->database, connector->host, connector->port, connector->username, connector->password);
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin", "mydb");
    connect_to_db(connector);
    destroy_db_connector(connector);
    return 0;
}