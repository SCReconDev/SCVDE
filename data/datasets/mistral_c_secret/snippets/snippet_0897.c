#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_FILE "test_config.txt"

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
    if (config->username == NULL) {
        free(config);
        return NULL;
    }

    config->password = strdup(password);
    if (config->password == NULL) {
        free(config->username);
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
        return -1;
    }

    fprintf(file, "Username: %s\n", config->username);
    fprintf(file, "Password: %s\n", config->password);

    fclose(file);

    return 0;
}

int main() {
    const char *test_username = getenv("TEST_USERNAME");
    if (test_username == NULL) {
        fprintf(stderr, "TEST_USERNAME environment variable not set\n");
        return 1;
    }

    const char *test_password = getenv("TEST_PASSWORD");
    if (test_password == NULL) {
        fprintf(stderr, "TEST_PASSWORD environment variable not set\n");
        return 1;
    }

    TestConfiguration *config = create_test_configuration(test_username, test_password);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    if (save_test_configuration(config) != 0) {
        fprintf(stderr, "Failed to save test configuration\n");
        destroy_test_configuration(config);
        return 1;
    }

    printf("Test configuration saved successfully\n");
    destroy_test_configuration(config);

    return 0;
}