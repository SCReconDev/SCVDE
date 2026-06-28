#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_PASSWORD_LENGTH 100

typedef struct {
    MYSQL* conn;
    char password[MAX_PASSWORD_LENGTH];
} DatabaseConnector;

DatabaseConnector* create_database_connector() {
    DatabaseConnector* connector = (DatabaseConnector*)malloc(sizeof(DatabaseConnector));
    if (connector == NULL) {
        return NULL;
    }

    const char* password_env = getenv("DB_PASSWORD");
    if (password_env == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        free(connector);
        return NULL;
    }

    strncpy(connector->password, password_env, MAX_PASSWORD_LENGTH - 1);
    connector->password[MAX_PASSWORD_LENGTH - 1] = '\0';

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, "localhost", "user", connector->password, "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector);
        return NULL;
    }

    return connector;
}

void execute_query(DatabaseConnector* connector, const char* query) {
    if (mysql_query(connector->conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }

    MYSQL_RES* result = mysql_store_result(connector->conn);
    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
}

void destroy_database_connector(DatabaseConnector* connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector);
    }
}

int main() {
    DatabaseConnector* connector = create_database_connector();
    if (connector == NULL) {
        return 1;
    }

    execute_query(connector, "SELECT * FROM table");
    destroy_database_connector(connector);

    return 0;
}