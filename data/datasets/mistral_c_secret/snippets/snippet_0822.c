#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    char* host;
    char* user;
    char* password;
    char* dbname;
} DbConnector;

DbConnector* create_db_connector() {
    DbConnector* connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(DB_HOST);
    connector->user = strdup(DB_USER);
    connector->dbname = strdup(DB_NAME);

    if (connector->host == NULL || connector->user == NULL || connector->dbname == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->dbname);
        free(connector);
        return NULL;
    }

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->dbname);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector* connector) {
    if (connector != NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->dbname);
        free(connector);
    }
}

int main() {
    DbConnector* connector = create_db_connector();
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created successfully\n");
    printf("Host: %s\n", connector->host);
    printf("User: %s\n", connector->user);
    printf("Password: %s\n", connector->password);
    printf("Database: %s\n", connector->dbname);

    destroy_db_connector(connector);
    return 0;
}