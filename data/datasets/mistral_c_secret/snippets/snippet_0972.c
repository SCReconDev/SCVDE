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

    const char *password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
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
        fprintf(stderr, "Error: MySQL initialization failed.\n");
        free(connector->host);
        free(connector->user);
        free(connector->password);
        free(connector->database);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: MySQL connection failed: %s\n", mysql_error(connector->conn));
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
    DbConnector *connector = create_db_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        return EXIT_FAILURE;
    }

    printf("Database connection established.\n");

    destroy_db_connector(connector);
    return EXIT_SUCCESS;
}