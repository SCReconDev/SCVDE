#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_FILE "test_config.json"

typedef struct {
    char *username;
    char *password;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *username, const char *password) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->username = strdup(username);
    config->password = strdup(password);

    if (config->username == NULL || config->password == NULL) {
        free(config->username);
        free(config->password);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->username);
        free(config->password);
        free(config);
    }
}

int save_test_configuration(TestConfiguration *config) {
    if (config == NULL) {
        return -1;
    }

    FILE *file = fopen(TEST_CONFIG_FILE, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open configuration file for writing.\n");
        return -1;
    }

    fprintf(file, "{\n");
    fprintf(file, "    \"username\": \"%s\",\n", config->username);
    fprintf(file, "    \"password\": \"%s\"\n", config->password);
    fprintf(file, "}\n");

    fclose(file);

    printf("Successfully saved test configuration.\n");

    return 0;
}

int main() {
    const char *username = getenv("TEST_USERNAME");
    const char *password = getenv("TEST_PASSWORD");

    if (username == NULL || password == NULL) {
        fprintf(stderr, "TEST_USERNAME or TEST_PASSWORD environment variable not set.\n");
        return 1;
    }

    TestConfiguration *config = create_test_configuration(username, password);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    if (save_test_configuration(config) != 0) {
        destroy_test_configuration(config);
        return 1;
    }

    destroy_test_configuration(config);

    return 0;
}