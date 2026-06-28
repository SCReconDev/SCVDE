#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_67890"

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", DB_PASSWORD, "test_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Connected to database\n");

    mysql_close(conn);
    return EXIT_SUCCESS;
}