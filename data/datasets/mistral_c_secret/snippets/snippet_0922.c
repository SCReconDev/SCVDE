#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"

int main(void) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *db_password = getenv("DB_PASSWORD");
    if (!db_password) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return 1;
    }

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, db_password, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "SELECT * FROM users")) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);
    if (res) {
        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("%s %s\n", row[0], row[1]);
        }
        mysql_free_result(res);
    }

    mysql_close(conn);

    return 0;
}