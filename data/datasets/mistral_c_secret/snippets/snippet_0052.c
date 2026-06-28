#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *database;
} DbConnection;

DbConnection *create_db_connection(const char *host, int port, const char *user, const char *database) {
    DbConnection *conn = (DbConnection *)malloc(sizeof(DbConnection));
    if (conn == NULL) {
        return NULL;
    }
    conn->host = strdup(host);
    conn->port = port;
    conn->user = strdup(user);
    conn->password = strdup(DB_PASSWORD);
    conn->database = strdup(database);
    return conn;
}

void destroy_db_connection(DbConnection *conn) {
    if (conn != NULL) {
        free(conn->host);
        free(conn->user);
        free(conn->password);
        free(conn->database);
        free(conn);
    }
}

int connect_to_db(DbConnection *conn) {
    if (conn == NULL) {
        return -1;
    }
    printf("Connecting to database %s on %s:%d with user %s and password %s\n",
           conn->database, conn->host, conn->port, conn->user, conn->password);
    return 0;
}

int main() {
    DbConnection *conn = create_db_connection("localhost", 5432, "admin", "test_db");
    if (conn == NULL) {
        fprintf(stderr, "Failed to create database connection\n");
        return 1;
    }
    connect_to_db(conn);
    destroy_db_connection(conn);
    return 0;
}