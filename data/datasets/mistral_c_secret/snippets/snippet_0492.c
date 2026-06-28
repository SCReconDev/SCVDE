#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->conn = mysql_init(NULL);
    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

int connect_to_db(DbConnector *connector) {
    if (!mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(connector->conn));
        return 1;
    }
    return 0;
}

void destroy_db_connector(DbConnector *connector) {
    mysql_close(connector->conn);
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector->database);
    free(connector);
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "root", "test_db");
    if (connect_to_db(connector) != 0) {
        destroy_db_connector(connector);
        return 1;
    }
    printf("Connected to database successfully\n");
    destroy_db_connector(connector);
    return 0;
}