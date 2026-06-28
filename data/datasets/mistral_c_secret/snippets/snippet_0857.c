#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_env;
    char *test_user;
    char *test_password;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_env, const char *test_user) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_env = strdup(test_env);
    config->test_user = strdup(test_user);
    if (config->test_env == NULL || config->test_user == NULL) {
        free(config->test_env);
        free(config->test_user);
        free(config);
        return NULL;
    }

    config->test_password = getenv("TEST_PASSWORD");
    if (config->test_password == NULL) {
        free(config->test_env);
        free(config->test_user);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->test_env != NULL) {
            free(config->test_env);
        }
        if (config->test_user != NULL) {
            free(config->test_user);
        }
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("staging", "testuser");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test configuration created for environment: %s\n", config->test_env);
    printf("Test user: %s\n", config->test_user);

    destroy_test_configuration(config);
    return 0;
}