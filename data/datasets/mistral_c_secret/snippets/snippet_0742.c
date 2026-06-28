#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *db;
    unsigned int port;
} DbConnector;

DbConnector* create_db_connector(const char *password) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup("localhost");
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->user = strdup("db_user");
    if (connector->user == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->db = strdup("test_db");
    if (connector->db == NULL) {
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->port = 3306;

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->db);
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, password, connector->db, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->db);
        free(connector->user);
        free(connector->host);
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
        free(connector->db);
        free(connector->user);
        free(connector->host);
        free(connector);
    }
}

int main() {
    const char *password = getenv("DB_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return 1;
    }

    DbConnector *connector = create_db_connector(password);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Connected to database: %s\n", connector->db);

    destroy_db_connector(connector);

    return 0;
}