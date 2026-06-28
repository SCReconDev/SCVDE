#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

char* get_db_password() {
    char* password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(password);
}

void connect_to_database(const char* host, const char* user, const char* password, const char* db) {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error: mysql_init failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, host, user, password, db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Connected to database: %s\n", db);
    mysql_close(conn);
}

int main() {
    char* password = get_db_password();
    connect_to_database("localhost", "root", password, "test_db");
    free(password);
    return 0;
}