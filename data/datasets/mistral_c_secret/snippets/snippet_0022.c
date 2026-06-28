#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "db_user"
#define DB_PASSWORD "fake_db_password_123"
#define DB_NAME "test_db"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DatabaseConnector;

DatabaseConnector *create_db_connector(const char *host) {
    DatabaseConnector *connector = (DatabaseConnector *)malloc(sizeof(DatabaseConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
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

    connector->password = strdup(DB_PASSWORD);
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector);
        return NULL;
    }

    connector->database = strdup(DB_NAME);
    if (connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DatabaseConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DatabaseConnector *connector = create_db_connector("localhost");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return EXIT_FAILURE;
    }

    printf("Database connector created with host: %s\n", connector->host);
    printf("Database user: %s\n", connector->user);
    printf("Database password: %s\n", connector->password);
    printf("Database name: %s\n", connector->database);

    destroy_db_connector(connector);
    return EXIT_SUCCESS;
}