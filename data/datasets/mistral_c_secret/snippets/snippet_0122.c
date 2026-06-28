#include <stdio.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_1234567890"

void connect_to_database() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "localhost", "db_user", DB_PASSWORD, "test_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return;
    }

    printf("Connected to database successfully\n");
    mysql_close(conn);
}

int main() {
    connect_to_database();
    return 0;
}