#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *db;
} DbConnector;

DbConnector *create_db_connector(const char *host, const char *user, const char *db) {
    DbConnector *connector = (DbConnector *)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->db = strdup(db);
    if (connector->host == NULL || connector->user == NULL || connector->db == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    char *password = getenv("DB_PASSWORD");
    if (password == NULL) {
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, password, connector->db, 0, NULL, 0) == NULL) {
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
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        if (connector->host != NULL) {
            free(connector->host);
        }
        if (connector->user != NULL) {
            free(connector->user);
        }
        if (connector->db != NULL) {
            free(connector->db);
        }
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database connector created for host: %s\n", connector->host);
    printf("Connected to database: %s\n", connector->db);

    destroy_db_connector(connector);
    return 0;
}