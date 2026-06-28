#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"
#define DB_PASS_ENV "DB_PASSWORD"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DbConnector;

DbConnector *create_db_connector() {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(DB_HOST);
    connector->user = strdup(DB_USER);
    connector->database = strdup(DB_NAME);
    connector->password = getenv(DB_PASS_ENV);

    if (connector->host == NULL || connector->user == NULL || connector->database == NULL || connector->password == NULL) {
        fprintf(stderr, "Memory allocation or environment variable error.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector();
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    printf("Database connection established successfully.\n");

    destroy_db_connector(connector);
    return 0;
}