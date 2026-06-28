#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *host;
    int port;
    char *username;
    char *password;
    char *database;
} DbConfig;

DbConfig *create_db_config() {
    DbConfig *config = (DbConfig *)malloc(sizeof(DbConfig));
    if (config == NULL) {
        return NULL;
    }

    config->host = getenv("DB_HOST");
    if (config->host == NULL) {
        fprintf(stderr, "DB_HOST environment variable not set\n");
        free(config);
        return NULL;
    }

    char *port_str = getenv("DB_PORT");
    if (port_str == NULL) {
        fprintf(stderr, "DB_PORT environment variable not set\n");
        free(config);
        return NULL;
    }
    config->port = atoi(port_str);

    config->username = getenv("DB_USERNAME");
    if (config->username == NULL) {
        fprintf(stderr, "DB_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    config->password = getenv("DB_PASSWORD");
    if (config->password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    config->database = getenv("DB_DATABASE");
    if (config->database == NULL) {
        fprintf(stderr, "DB_DATABASE environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_db_config(DbConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    DbConfig *config = create_db_config();
    if (config == NULL) {
        return 1;
    }

    printf("Database Configuration:\n");
    printf("Host: %s\n", config->host);
    printf("Port: %d\n", config->port);
    printf("Username: %s\n", config->username);
    printf("Password: %s\n", config->password);
    printf("Database: %s\n", config->database);

    destroy_db_config(config);
    return 0;
}