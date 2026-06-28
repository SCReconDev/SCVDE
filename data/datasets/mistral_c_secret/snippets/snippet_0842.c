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

DbConnector* create_db_connector(const char *host, const char *user, const char *db, unsigned int port) {
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

    connector->db = strdup(db);
    if (connector->db == NULL) {
        free(connector->user);
        free(connector->host);
        free(connector);
        return NULL;
    }

    connector->port = port;
    connector->conn = NULL;

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        if (connector->conn != NULL) {
            mysql_close(connector->conn);
        }
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
    }
}

int connect_to_db(DbConnector *connector) {
    if (connector == NULL) {
        return -1;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        return -1;
    }

    const char *password = getenv("DB_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        return -1;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, password, connector->db, connector->port, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(connector->conn));
        return -1;
    }

    return 0;
}

int execute_query(DbConnector *connector, const char *query, MYSQL_RES **result) {
    if (connector == NULL || query == NULL || result == NULL) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(connector->conn));
        return -1;
    }

    *result = mysql_store_result(connector->conn);
    if (*result == NULL) {
        fprintf(stderr, "Failed to store result: %s\n", mysql_error(connector->conn));
        return -1;
    }

    return 0;
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "db_user", "test_db", 3306);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create database connector.\n");
        return 1;
    }

    if (connect_to_db(connector) != 0) {
        fprintf(stderr, "Failed to connect to database.\n");
        destroy_db_connector(connector);
        return 1;
    }

    MYSQL_RES *result = NULL;
    if (execute_query(connector, "SELECT * FROM users", &result) != 0) {
        fprintf(stderr, "Failed to execute query.\n");
        destroy_db_connector(connector);
        return 1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    destroy_db_connector(connector);

    return 0;
}