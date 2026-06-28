#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"

int main(int argc, char **argv) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = "SELECT * FROM users";

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    char *db_password = getenv("DB_PASSWORD");
    if(db_password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, db_password, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s %s\n", row[0], row[1]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}