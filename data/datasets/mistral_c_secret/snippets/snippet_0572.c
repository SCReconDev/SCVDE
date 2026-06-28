#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    MYSQL* conn;
    char* host;
    char* user;
    char* password;
    char* database;
} DbConnector;

DbConnector* create_db_connector() {
    DbConnector* connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(DB_HOST);
    connector->user = strdup(DB_USER);
    connector->database = strdup(DB_NAME);
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
        fprintf(stderr, "Error: mysql_init() failed\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }
    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_db_connector(DbConnector* connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
    }
}

int query_data(DbConnector* connector, const char* query) {
    if (connector == NULL || connector->conn == NULL) {
        return -1;
    }
    if (mysql_query(connector->conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(connector->conn));
        return -1;
    }
    MYSQL_RES* result = mysql_store_result(connector->conn);
    if (result == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(connector->conn));
        return -1;
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(result);
    return 0;
}

int main() {
    DbConnector* connector = create_db_connector();
    if (connector == NULL) {
        return 1;
    }
    query_data(connector, "SELECT * FROM test_table");
    destroy_db_connector(connector);
    return 0;
}