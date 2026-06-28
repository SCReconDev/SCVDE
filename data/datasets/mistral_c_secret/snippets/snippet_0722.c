#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
    unsigned int port;
} DatabaseConnector;

DatabaseConnector* create_database_connector() {
    DatabaseConnector *connector = (DatabaseConnector*)malloc(sizeof(DatabaseConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = getenv("DB_HOST");
    if (connector->host == NULL) {
        fprintf(stderr, "DB_HOST environment variable not set.\n");
        free(connector);
        return NULL;
    }

    connector->user = getenv("DB_USER");
    if (connector->user == NULL) {
        fprintf(stderr, "DB_USER environment variable not set.\n");
        free(connector);
        return NULL;
    }

    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        free(connector);
        return NULL;
    }

    connector->database = getenv("DB_NAME");
    if (connector->database == NULL) {
        fprintf(stderr, "DB_NAME environment variable not set.\n");
        free(connector);
        return NULL;
    }

    char *port_str = getenv("DB_PORT");
    if (port_str == NULL) {
        fprintf(stderr, "DB_PORT environment variable not set.\n");
        free(connector);
        return NULL;
    }
    connector->port = (unsigned int)atoi(port_str);

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_database_connector(DatabaseConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector);
    }
}

int main() {
    DatabaseConnector *connector = create_database_connector();
    if (connector == NULL) {
        return EXIT_FAILURE;
    }

    printf("Database Connector created successfully.\n");
    printf("Host: %s\n", connector->host);
    printf("User: %s\n", connector->user);
    printf("Database: %s\n", connector->database);
    printf("Port: %u\n", connector->port);

    destroy_database_connector(connector);
    return EXIT_SUCCESS;
}