#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_NAME "database"
#define DB_PASSWORD_ENV "DB_PASSWORD"

typedef struct {
    char *host;
    char *user;
    char *password;
    char *dbname;
} DbConnector;

DbConnector *create_db_connector() {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(DB_HOST);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->user = strdup(DB_USER);
    if (connector->user == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->dbname = strdup(DB_NAME);
    if (connector->dbname == NULL) {
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    char *password = getenv(DB_PASSWORD_ENV);
    if (password == NULL) {
        free(connector->dbname);
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector->dbname);
        free(connector->user);
        free(connector->host);
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
        free(connector->dbname);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector();
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created with Host: %s, User: %s, Password: %s, DBName: %s\n",
           connector->host, connector->user, connector->password, connector->dbname);

    destroy_db_connector(connector);
    return 0;
}