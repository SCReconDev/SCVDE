#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST_ENV_VAR "DB_HOST"
#define DB_USER_ENV_VAR "DB_USER"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"
#define DB_NAME_ENV_VAR "DB_NAME"

typedef struct {
    char *host;
    char *user;
    char *password;
    char *name;
} DbConnector;

DbConnector *create_db_connector() {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    char *host = getenv(DB_HOST_ENV_VAR);
    char *user = getenv(DB_USER_ENV_VAR);
    char *password = getenv(DB_PASSWORD_ENV_VAR);
    char *name = getenv(DB_NAME_ENV_VAR);

    if (host == NULL || user == NULL || password == NULL || name == NULL) {
        fprintf(stderr, "Error: Database credentials not found in environment variables.\n");
        free(connector);
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->password = strdup(password);
    connector->name = strdup(name);

    if (connector->host == NULL || connector->user == NULL ||
        connector->password == NULL || connector->name == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->name);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->name);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector();
    if (connector == NULL) {
        return 1;
    }

    printf("Database Connector created successfully.\n");
    printf("Host: %s\n", connector->host);
    printf("User: %s\n", connector->user);
    printf("Password: %s\n", connector->password);
    printf("Name: %s\n", connector->name);

    destroy_db_connector(connector);
    return 0;
}