#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_USER "admin"
#define DB_PASSWORD "password123"
#define DB_NAME "test_db"

int connect_to_database() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        return 1;
    }

    printf("Successfully connected to database.\n");
    mysql_close(conn);

    return 0;
}

int main() {
    connect_to_database();

    return 0;
}