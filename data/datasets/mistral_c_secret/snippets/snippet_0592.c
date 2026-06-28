#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    PGconn *conn;
    char *db_name;
    char *user;
    char *password;
    char *host;
    char *port;
} DbConnector;

DbConnector* create_db_connector(const char *db_name, const char *user, const char *host, const char *port) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->db_name = strdup(db_name);
    connector->user = strdup(user);
    connector->host = strdup(host);
    connector->port = strdup(port);

    const char *password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Database password not found in environment variables.\n");
        free(connector->db_name);
        free(connector->user);
        free(connector->host);
        free(connector->port);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector->db_name);
        free(connector->user);
        free(connector->host);
        free(connector->port);
        free(connector);
        return NULL;
    }

    char conninfo[512];
    snprintf(conninfo, sizeof(conninfo), "dbname=%s user=%s password=%s host=%s port=%s",
             connector->db_name, connector->user, connector->password, connector->host, connector->port);

    connector->conn = PQconnectdb(conninfo);
    if (PQstatus(connector->conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(connector->conn));
        PQfinish(connector->conn);
        free(connector->db_name);
        free(connector->user);
        free(connector->password);
        free(connector->host);
        free(connector->port);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        PQfinish(connector->conn);
        free(connector->db_name);
        free(connector->user);
        free(connector->password);
        free(connector->host);
        free(connector->port);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("mydb", "myuser", "localhost", "5432");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    printf("Database connector created successfully.\n");
    printf("Database Name: %s\n", connector->db_name);
    printf("User: %s\n", connector->user);
    printf("Host: %s\n", connector->host);
    printf("Port: %s\n", connector->port);

    destroy_db_connector(connector);
    return 0;
}