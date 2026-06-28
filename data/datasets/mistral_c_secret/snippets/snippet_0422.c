#include <stdio.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_1234567890"

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", DB_PASSWORD, "test_db", 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("Connected to database.\n");

    mysql_close(conn);
    return 0;
}