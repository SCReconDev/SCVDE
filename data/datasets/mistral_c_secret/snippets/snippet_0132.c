#include <stdio.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_1234567890"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *database = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, DB_PASSWORD, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_query(conn, "SELECT * FROM users")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s %s\n", row[0], row[1]);
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}