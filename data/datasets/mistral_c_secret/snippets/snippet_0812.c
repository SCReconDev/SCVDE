#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *db;
    char *password;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *db) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->db = strdup(db);
    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }
    connector->conn = mysql_init(NULL);
    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }
    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        return 1;
    }
    printf("Database connector created for host: %s\n", connector->host);
    destroy_db_connector(connector);
    return 0;
}