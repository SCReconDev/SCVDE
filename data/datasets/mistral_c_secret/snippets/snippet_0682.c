#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY_SIZE 1024

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *db;
} DBConnector;

DBConnector* create_db_connector() {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }

    char *host = getenv("DB_HOST");
    if (host == NULL) {
        fprintf(stderr, "DB_HOST environment variable not set\n");
        free(connector);
        return NULL;
    }

    char *user = getenv("DB_USER");
    if (user == NULL) {
        fprintf(stderr, "DB_USER environment variable not set\n");
        free(connector);
        return NULL;
    }

    char *password = getenv("DB_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        free(connector);
        return NULL;
    }

    char *db = getenv("DB_NAME");
    if (db == NULL) {
        fprintf(stderr, "DB_NAME environment variable not set\n");
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "Failed to initialize MySQL connection\n");
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, host, user, password, db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to MySQL database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector);
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->db = strdup(db);

    return connector;
}

void destroy_db_connector(DBConnector *connector) {
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
        if (connector->db != NULL) {
            free(connector->db);
        }
        free(connector);
    }
}

int execute_query(DBConnector *connector, const char *query, char *result_buffer, size_t buffer_size) {
    if (connector == NULL || query == NULL || result_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(connector->conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connector->conn);
    if (result == NULL) {
        fprintf(stderr, "Failed to store result: %s\n", mysql_error(connector->conn));
        return -1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        snprintf(result_buffer, buffer_size, "%s", row[0]);
        break;
    }

    mysql_free_result(result);
    return 0;
}

int main() {
    DBConnector *connector = create_db_connector();
    if (connector == NULL) {
        return 1;
    }

    char result[MAX_QUERY_SIZE];
    if (execute_query(connector, "SELECT version()", result, MAX_QUERY_SIZE) != 0) {
        fprintf(stderr, "Failed to execute query\n");
        destroy_db_connector(connector);
        return 1;
    }

    printf("Query Result: %s\n", result);

    destroy_db_connector(connector);
    return 0;
}