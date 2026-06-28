#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *database;
} DbConfig;

DbConfig* create_db_config(const char *host, int port, const char *user, const char *password, const char *database) {
    DbConfig *config = (DbConfig*)malloc(sizeof(DbConfig));
    config->host = strdup(host);
    config->port = port;
    config->user = strdup(user);
    config->password = strdup(password);
    config->database = strdup(database);
    return config;
}

void destroy_db_config(DbConfig *config) {
    free(config->host);
    free(config->user);
    free(config->password);
    free(config->database);
    free(config);
}

void connect_to_database(DbConfig *config) {
    printf("Connecting to database at %s:%d\n", config->host, config->port);
    printf("Using credentials: %s:%s\n", config->user, config->password);
    printf("Database: %s\n", config->database);
}

int main() {
    const char *db_password = getenv("DB_PASSWORD");
    if (db_password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        return 1;
    }

    DbConfig *config = create_db_config("localhost", 5432, "admin", db_password, "test_db");
    connect_to_database(config);
    destroy_db_config(config);

    return 0;
}