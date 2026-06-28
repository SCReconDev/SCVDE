#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
    unsigned int port;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *database, unsigned int port) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->database = strdup(database);
    connector->port = port;

    if (connector->host == NULL || connector->user == NULL || connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    char *password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Database password not found in environment variables\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "Failed to initialize MySQL connection\n");
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password,
                          connector->database, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
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

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "root", "test_db", 3306);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database connector created successfully\n");
    destroy_db_connector(connector);

    return 0;
}