#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_PASSWORD "password123"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DBConnector;

DBConnector *create_db_connector(const char *host, const char *user, const char *database) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->password = strdup(DB_PASSWORD);
    connector->database = strdup(database);
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector->password);
    free(connector->database);
    free(connector);
}

void connect_to_db(DBConnector *connector) {
    connector->conn = mysql_init(NULL);
    if (!mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(connector->conn));
        exit(1);
    }
    printf("Connected to database: %s\n", connector->database);
}

void disconnect_from_db(DBConnector *connector) {
    mysql_close(connector->conn);
}

int main() {
    DBConnector *connector = create_db_connector("localhost", "root", "test_db");
    connect_to_db(connector);
    disconnect_from_db(connector);
    destroy_db_connector(connector);
    return 0;
}