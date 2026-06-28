#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DBConnector;

DBConnector *create_connector(const char *host, const char *user, const char *database) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    if (connector == NULL) {
        return NULL;
    }
    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->database = strdup(database);
    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }
    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }
    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_connector(DBConnector *connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DBConnector *connector = create_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create connector\n");
        return 1;
    }
    printf("Connected to database\n");
    destroy_connector(connector);
    return 0;
}