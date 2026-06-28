#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *test_mode;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *password) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->username = strdup("test_user");
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

    config->test_mode = strdup("enabled");
    if (config->test_mode == NULL) {
        free(config->password);
        free(config->username);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_mode);
        free(config->password);
        free(config->username);
        free(config);
    }
}

int main() {
    const char *password = getenv("TEST_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "TEST_PASSWORD environment variable not set\n");
        return 1;
    }

    TestConfiguration *config = create_test_configuration(password);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with username: %s\n", config->username);
    printf("Password: %s\n", config->password);
    printf("Test mode: %s\n", config->test_mode);

    destroy_test_configuration(config);

    return 0;
}