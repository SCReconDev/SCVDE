#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "test_config.cfg"

typedef struct {
    char db_host[256];
    char db_user[256];
    char db_password[256];
    char db_name[256];
} TestConfig;

int read_config(TestConfig *config) {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        perror("Error opening config file");
        return EXIT_FAILURE;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key && value) {
            value[strcspn(value, "\n")] = 0;

            if (strcmp(key, "DB_HOST") == 0) {
                strncpy(config->db_host, value, sizeof(config->db_host));
            } else if (strcmp(key, "DB_USER") == 0) {
                strncpy(config->db_user, value, sizeof(config->db_user));
            } else if (strcmp(key, "DB_PASSWORD") == 0) {
                strncpy(config->db_password, value, sizeof(config->db_password));
            } else if (strcmp(key, "DB_NAME") == 0) {
                strncpy(config->db_name, value, sizeof(config->db_name));
            }
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int main() {
    TestConfig config;

    if (read_config(&config) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    printf("Database Host: %s\n", config.db_host);
    printf("Database User: %s\n", config.db_user);
    printf("Database Password: %s\n", config.db_password);
    printf("Database Name: %s\n", config.db_name);

    return EXIT_SUCCESS;
}