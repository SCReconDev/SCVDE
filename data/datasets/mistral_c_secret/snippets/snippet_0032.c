#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_1234567890"

void connect_to_database() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "root", DB_PASSWORD, "test_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(1);
    }

    printf("Connected to database\n");
    mysql_close(conn);
}

int main() {
    connect_to_database();
    return 0;
}