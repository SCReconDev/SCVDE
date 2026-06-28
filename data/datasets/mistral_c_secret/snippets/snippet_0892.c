#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
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

    if (mysql_real_connect(connector->conn, DB_HOST, DB_USER, connector->password, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
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

int query_data(DbConnector *connector, const char *query, MYSQL_RES **result) {
    if (connector == NULL || query == NULL || result == NULL) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(connector->conn));
        return -1;
    }

    *result = mysql_store_result(connector->conn);
    if (*result == NULL) {
        fprintf(stderr, "Failed to store result: %s\n", mysql_error(connector->conn));
        return -1;
    }

    return 0;
}

int main() {
    const char *db_password = getenv("DB_PASSWORD");
    if (db_password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return 1;
    }

    DbConnector *connector = create_db_connector(db_password);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    MYSQL_RES *result = NULL;
    if (query_data(connector, "SELECT * FROM test_table", &result) != 0) {
        fprintf(stderr, "Failed to query data\n");
        destroy_db_connector(connector);
        return 1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    destroy_db_connector(connector);

    return 0;
}