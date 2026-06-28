#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
    unsigned int port;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *password, const char *database, unsigned int port) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->password = strdup(password);
    connector->database = strdup(database);
    connector->port = port;

    if (connector->host == NULL || connector->user == NULL || connector->password == NULL || connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
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

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, connector->port, NULL, 0) == NULL) {
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

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int execute_query(DbConnector *connector, const char *query, char *result_buffer, size_t buffer_size) {
    if (connector == NULL || query == NULL || result_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connector->conn);
    if (result == NULL) {
        return -1;
    }

    MYSQL_ROW row;
    size_t offset = 0;
    while ((row = mysql_fetch_row(result)) != NULL) {
        for (unsigned int i = 0; i < mysql_num_fields(result); i++) {
            if (row[i] != NULL) {
                size_t len = strlen(row[i]);
                if (offset + len + 1 >= buffer_size) {
                    mysql_free_result(result);
                    return -1;
                }
                strcpy(result_buffer + offset, row[i]);
                offset += len;
                result_buffer[offset++] = '\t';
            }
        }
        result_buffer[offset++] = '\n';
    }

    result_buffer[offset] = '\0';
    mysql_free_result(result);

    return 0;
}

int main() {
    const char *host = "localhost";
    const char *user = "db_user";
    const char *password_env = getenv("DB_PASSWORD");
    const char *database = "test_db";
    unsigned int port = 3306;

    if (password_env == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        return 1;
    }

    DbConnector *connector = create_db_connector(host, user, password_env, database, port);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    char result_buffer[MAX_BUFFER_SIZE];
    if (execute_query(connector, "SELECT * FROM users", result_buffer, sizeof(result_buffer)) != 0) {
        fprintf(stderr, "Failed to execute query.\n");
        destroy_db_connector(connector);
        return 1;
    }

    printf("Query Result:\n%s\n", result_buffer);

    destroy_db_connector(connector);

    return 0;
}