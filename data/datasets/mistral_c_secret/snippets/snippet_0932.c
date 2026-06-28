#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *database;
} DbConnector;

DbConnector* create_db_connector(const char *host, int port, const char *user, const char *database) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->port = port;

    connector->user = strdup(user);
    if (connector->user == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->user);
        free(connector);
        return NULL;
    }

    connector->database = strdup(database);
    if (connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin", "mydb");
    if (connector == NULL) {
        return 1;
    }

    printf("Database Connector created successfully.\n");
    printf("Host: %s\n", connector->host);
    printf("Port: %d\n", connector->port);
    printf("User: %s\n", connector->user);
    printf("Password: %s\n", connector->password);
    printf("Database: %s\n", connector->database);

    destroy_db_connector(connector);
    return 0;
}