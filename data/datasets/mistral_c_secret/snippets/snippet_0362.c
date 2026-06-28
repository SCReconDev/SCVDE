#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *db_host;
    int db_port;
    char *db_user;
    char *db_password;
} DbConnector;

DbConnector *create_db_connector(const char *host, int port, const char *user) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->db_host = strdup(host);
    connector->db_port = port;
    connector->db_user = strdup(user);
    connector->db_password = strdup(DB_PASSWORD);

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        free(connector->db_host);
        free(connector->db_user);
        free(connector->db_password);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", 5432, "admin");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database Connector created with host: %s, port: %d, user: %s\n",
           connector->db_host, connector->db_port, connector->db_user);
    printf("Database Password: %s\n", connector->db_password);

    destroy_db_connector(connector);
    return 0;
}