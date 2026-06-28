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
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *database) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    if (connector->host == NULL) {
        free(connector);
        return NULL;
    }

    connector->user = strdup(user);
    if (connector->user == NULL) {
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->database = strdup(database);
    if (connector->database == NULL) {
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        free(connector->database);
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        free(connector->password);
        free(connector->database);
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, 0, NULL, 0) == NULL) {
        mysql_close(connector->conn);
        free(connector->password);
        free(connector->database);
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
        if (connector->password != NULL) {
            free(connector->password);
        }
        if (connector->database != NULL) {
            free(connector->database);
        }
        if (connector->user != NULL) {
            free(connector->user);
        }
        if (connector->host != NULL) {
            free(connector->host);
        }
        free(connector);
    }
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "user", "mydb");
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    printf("Database connector created with host: %s\n", connector->host);
    printf("Database connector created with user: %s\n", connector->user);
    printf("Database connector created with database: %s\n", connector->database);

    destroy_db_connector(connector);
    return 0;
}