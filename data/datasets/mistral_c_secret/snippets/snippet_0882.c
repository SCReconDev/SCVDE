#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    MYSQL *conn;
    char *db_host;
    char *db_user;
    char *db_name;
    char *db_password;
} DbConnector;

DbConnector* create_db_connector(const char *db_host, const char *db_user, const char *db_name) {
    DbConnector *connector = (DbConnector*)malloc(sizeof(DbConnector));
    if (connector == NULL) {
        return NULL;
    }
    connector->db_host = strdup(db_host);
    connector->db_user = strdup(db_user);
    connector->db_name = strdup(db_name);
    connector->db_password = getenv("DB_PASSWORD");
    if (connector->db_password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        free(connector->db_host);
        free(connector->db_user);
        free(connector->db_name);
        free(connector);
        return NULL;
    }

    connector->conn = mysql_init(NULL);
    if (connector->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(connector->db_host);
        free(connector->db_user);
        free(connector->db_name);
        free(connector);
        return NULL;
    }

    if (mysql_real_connect(connector->conn, connector->db_host, connector->db_user, connector->db_password, connector->db_name, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(connector->conn);
        free(connector->db_host);
        free(connector->db_user);
        free(connector->db_name);
        free(connector);
        return NULL;
    }

    return connector;
}

void destroy_db_connector(DbConnector *connector) {
    if (connector != NULL) {
        mysql_close(connector->conn);
        free(connector->db_host);
        free(connector->db_user);
        free(connector->db_name);
        free(connector);
    }
}

int execute_query(DbConnector *connector, const char *query) {
    if (mysql_query(connector->conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(connector->conn));
        return 1;
    }
    return 0;
}

int main() {
    DbConnector *connector = create_db_connector("localhost", "root", "test_db");
    if (connector == NULL) {
        return 1;
    }

    execute_query(connector, "SELECT * FROM users");
    execute_query(connector, "INSERT INTO posts (title, content) VALUES ('Test', 'This is a test post')");

    destroy_db_connector(connector);
    return 0;
}