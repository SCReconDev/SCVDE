#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "db_user"
#define DB_NAME "test_db"

typedef struct {
    MYSQL *conn;
    char *password;
} DBConnector;

DBConnector* create_connector() {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, DB_HOST, DB_USER, connector->password, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_connector(DBConnector *connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector);
    }
}

int main() {
    DBConnector *connector = create_connector();
    if (connector == NULL) {
        return 1;
    }

    printf("Database connector created with password: %s\n", connector->password);
    destroy_connector(connector);
    return 0;
}