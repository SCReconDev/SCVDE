#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_user;
    char *test_password;
    char *test_url;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_url) {
    TestConfiguration *config = malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_url = strdup(test_url);
    if (config->test_url == NULL) {
        free(config);
        return NULL;
    }

    config->test_user = getenv("TEST_USER");
    if (config->test_user == NULL) {
        free(config->test_url);
        free(config);
        return NULL;
    }

    config->test_password = getenv("TEST_PASSWORD");
    if (config->test_password == NULL) {
        free(config->test_user);
        free(config->test_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->test_url != NULL) {
            free(config->test_url);
        }
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("https://test.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create Test Configuration\n");
        return 1;
    }

    printf("Test Configuration created with test password: %s\n", config->test_password);

    destroy_test_configuration(config);
    return 0;
}