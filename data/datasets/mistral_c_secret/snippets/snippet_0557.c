#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_DB_URL_ENV "TEST_DB_URL"
#define TEST_DB_USER_ENV "TEST_DB_USER"
#define TEST_DB_PASS_ENV "TEST_DB_PASS"

typedef struct {
    char *url;
    char *user;
    char *password;
} TestConfig;

TestConfig *create_test_config() {
    TestConfig *config = (TestConfig *)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }

    config->url = getenv(TEST_DB_URL_ENV);
    config->user = getenv(TEST_DB_USER_ENV);
    config->password = getenv(TEST_DB_PASS_ENV);

    if (config->url == NULL || config->user == NULL || config->password == NULL) {
        fprintf(stderr, "Environment variable error.\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    TestConfig *config = create_test_config();
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test configuration created successfully.\n");
    printf("URL: %s\n", config->url);
    printf("User: %s\n", config->user);
    printf("Password: %s\n", config->password);

    destroy_test_config(config);
    return 0;
}