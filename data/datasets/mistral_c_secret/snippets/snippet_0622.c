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
    unsigned int port;
} DbConnector;

DbConnector* create_db_connector(const char *host, const char *user, const char *password, const char *database, unsigned int port) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }

    connector->host = strdup(host);
    connector->user = strdup(user);
    connector->password = strdup(password);
    connector->database = strdup(database);
    connector->port = port;

    if (connector->host == NULL || connector->user == NULL || connector->password == NULL || connector->database == NULL) {
        free(connector->host);
        free(connector->user);
        free(connector->password);
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

int connect_to_db(DbConnector *connector) {
    if (connector == NULL || connector->conn == NULL || connector->host == NULL || connector->user == NULL || connector->password == NULL || connector->database == NULL) {
        return -1;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->database, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
        return -1;
    }

    return 0;
}

int main() {
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_DATABASE");
    const char *port_str = getenv("DB_PORT");

    if (host == NULL || user == NULL || password == NULL || database == NULL || port_str == NULL) {
        fprintf(stderr, "Database environment variables not set\n");
        return 1;
    }

    unsigned int port = (unsigned int)atoi(port_str);

    DbConnector *connector = create_db_connector(host, user, password, database, port);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector\n");
        return 1;
    }

    if (connect_to_db(connector) != 0) {
        fprintf(stderr, "Failed to connect to database\n");
        destroy_db_connector(connector);
        return 1;
    }

    printf("Successfully connected to the database\n");

    destroy_db_connector(connector);
    return 0;
}