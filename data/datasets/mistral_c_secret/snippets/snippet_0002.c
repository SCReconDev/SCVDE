#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
} DbConfig;

DbConfig *create_db_config(const char *host, int port, const char *user) {
    DbConfig *config = (DbConfig *)malloc(sizeof(DbConfig));
    config->host = strdup(host);
    config->port = port;
    config->user = strdup(user);
    config->password = strdup(DB_PASSWORD);
    return config;
}

void destroy_db_config(DbConfig *config) {
    free(config->host);
    free(config->user);
    free(config->password);
    free(config);
}

int main() {
    DbConfig *config = create_db_config("localhost", 5432, "admin");
    printf("Database config created with password: %s\n", config->password);
    destroy_db_config(config);
    return 0;
}