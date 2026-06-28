#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"

typedef struct {
    MYSQL *conn;
    char *password;
} DbConnector;

DbConnector *create_db_connector(const char *password) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->password);
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
        free(connector->password);
        free(connector);
    }
}

int connect_to_db(DbConnector *connector) {
    if (connector == NULL || connector->password == NULL) {
        return -1;
    }

    if (mysql_real_connect(connector->conn, DB_HOST, DB_USER, connector->password, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
        return -1;
    }

    printf("Successfully connected to the database.\n");

    return 0;
}

int main() {
    const char *password = getenv("DB_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        return 1;
    }

    DbConnector *connector = create_db_connector(password);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    if (connect_to_db(connector) != 0) {
        destroy_db_connector(connector);
        return 1;
    }

    destroy_db_connector(connector);

    return 0;
}