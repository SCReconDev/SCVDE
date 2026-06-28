#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
    unsigned int port;
} DatabaseConnector;

DatabaseConnector *create_database_connector(const char *host, const char *user, const char *database, unsigned int port) {
    DatabaseConnector *connector = (DatabaseConnector *)malloc(sizeof(DatabaseConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->database = strdup(database);
    connector->port = port;

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "Error: Failed to initialize MySQL connection.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector->password);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "Error: Failed to connect to MySQL database.\n");
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector->password);
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
        if (connector->host != NULL) {
            free(connector->host);
        }
        if (connector->user != NULL) {
            free(connector->user);
        }
        if (connector->database != NULL) {
            free(connector->database);
        }
        if (connector->password != NULL) {
            free(connector->password);
        }
        free(connector);
    }
}

int main() {
    const char *host = "localhost";
    const char *user = "db_user";
    const char *database = "test_db";
    unsigned int port = 3306;

    DatabaseConnector *connector = create_database_connector(host, user, database, port);

    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    printf("Database Connector created with host: %s, user: %s, database: %s, port: %u\n", connector->host, connector->user, connector->database, connector->port);

    destroy_database_connector(connector);
    return 0;
}