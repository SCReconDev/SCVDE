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
} DBConnector;

DBConnector* create_db_connector(const char *host, const char *user, const char *db) {
    DBConnector *connector = (DBConnector*)malloc(sizeof(DBConnector));
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

    connector->password = getenv("DB_PASSWORD");
    if (connector->password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DBConnector *connector) {
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

int execute_query(DBConnector *connector, const char *query, MYSQL_RES **result) {
    if (connector == NULL || query == NULL || result == NULL) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(connector->conn));
        return -1;
    }

    *result = mysql_store_result(connector->conn);
    if (*result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(connector->conn));
        return -1;
    }

    return 0;
}