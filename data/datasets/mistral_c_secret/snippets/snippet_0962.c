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
} DatabaseConnector;

DatabaseConnector *create_database_connector(const char *host, const char *user, const char *database) {
    DatabaseConnector *connector = (DatabaseConnector *)malloc(sizeof(DatabaseConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->user = strdup(user);
    if (connector->user == NULL) {
        free(connector->host);
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

    char *password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "Failed to initialize MySQL connection.\n");
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to MySQL database: %s\n", mysql_error(connector->conn));
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

void destroy_database_connector(DatabaseConnector *connector) {
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
    DatabaseConnector *connector = create_database_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    printf("Database connector created successfully.\n");
    printf("Host: %s\n", connector->host);
    printf("User: %s\n", connector->user);
    printf("Database: %s\n", connector->database);

    destroy_database_connector(connector);
    return 0;
}