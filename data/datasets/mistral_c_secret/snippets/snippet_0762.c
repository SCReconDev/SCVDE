#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_NAME "mydb"
#define DB_PASS_ENV "DB_PASSWORD"

typedef struct {
    char *host;
    char *user;
    char *password;
    char *dbname;
} DbConnector;

DbConnector* create_db_connector() {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(DB_HOST);
    connector->user = strdup(DB_USER);
    connector->dbname = strdup(DB_NAME);
    connector->password = getenv(DB_PASS_ENV);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->user);
        free(connector->dbname);
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

int connect_to_db(DbConnector *connector) {
    if (connector == NULL || connector->password == NULL) {
        return -1;
    }
    printf("Connecting to database %s at %s with user %s and password %s\n",
           connector->dbname, connector->host, connector->user, connector->password);
    return 0;
}

int main() {
    DbConnector *connector = create_db_connector();
    if (connector == NULL) {
        return 1;
    }
    connect_to_db(connector);
    destroy_db_connector(connector);
    return 0;
}