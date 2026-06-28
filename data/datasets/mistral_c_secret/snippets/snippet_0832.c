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

DBConnector *create_db_connector(const char *host, const char *user, const char *db, const char *password) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
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
        free(connector->host);
        free(connector->user);
        free(connector);
        return NULL;
    }

    connector->password = strdup(password);
    if (connector->password == NULL) {
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
        free(connector->password);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->host, connector->user, connector->password, connector->db, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(connector->conn));
        mysql_close(connector->conn);
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector->password);
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
        free(connector->host);
        free(connector->user);
        free(connector->db);
        free(connector->password);
        free(connector);
    }
}

int execute_query(DBConnector *connector, const char *query) {
    if (connector == NULL || query == NULL) {
        return -1;
    }

    if (mysql_query(connector->conn, query) != 0) {
        fprintf(stderr, "Error: %s\n", mysql_error(connector->conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connector->conn);
    if (result == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(connector->conn));
        return -1;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);

    return 0;
}

int main() {
    const char *db_password = getenv("DB_PASSWORD");
    if (db_password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return 1;
    }

    DBConnector *connector = create_db_connector("localhost", "root", "test_db", db_password);
    if (connector == NULL) {
        fprintf(stderr, "Failed to create DB connector\n");
        return 1;
    }

    execute_query(connector, "SELECT * FROM users");

    destroy_db_connector(connector);

    return 0;
}