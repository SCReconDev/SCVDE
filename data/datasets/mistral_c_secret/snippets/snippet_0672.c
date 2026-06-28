#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char *host;
    char *user;
    char *password;
    char *database;
    MYSQL *conn;
} DbConnector;

DbConnector* create_db_connector() {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = getenv("DB_HOST");
    connector->user = getenv("DB_USER");
    connector->password = getenv("DB_PASSWORD");
    connector->database = getenv("DB_NAME");

    if (connector->host == NULL || connector->user == NULL ||
        connector->password == NULL || connector->database == NULL) {
        fprintf(stderr, "DB_HOST, DB_USER, DB_PASSWORD, and DB_NAME environment variables must be set.\n");
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user,
                           connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector();
    if (connector == NULL) {
        return EXIT_FAILURE;
    }

    printf("Connected to database: %s\n", connector->database);

    destroy_db_connector(connector);
    return EXIT_SUCCESS;
}