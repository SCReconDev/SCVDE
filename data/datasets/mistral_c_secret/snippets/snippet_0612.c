#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_NAME "test_db"
#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

typedef struct {
    MYSQL *conn;
    char *host;
    char *user;
    char *password;
    char *database;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->database = strdup(database);

    if (connector->host == NULL || connector->user == NULL || connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->password = getenv(DB_PASSWORD_ENV_VAR);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "Error: MySQL initialization failed.\n");
        free(connector->host);
        free(connector->user);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password,
                          connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: MySQL connection failed: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
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
        if (connector->host != NULL) {
            free(connector->host);
        }
        if (connector->user != NULL) {
            free(connector->user);
        }
        if (connector->database != NULL) {
            free(connector->database);
        }
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector(DB_HOST, DB_USER, DB_NAME);
    if (connector == NULL) {
        return 1;
    }

    printf("Database connection established successfully.\n");
    printf("Host: %s\n", connector->host);
    printf("User: %s\n", connector->user);
    printf("Database: %s\n", connector->database);

    destroy_db_connector(connector);
    return 0;
}