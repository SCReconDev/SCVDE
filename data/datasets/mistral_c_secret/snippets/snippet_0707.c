#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_username;
    char *test_password;
    char *test_database;
} TestConfig;

TestConfig *create_test_config() {
    TestConfig *config = (TestConfig *)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }

    config->test_username = getenv("TEST_USERNAME");
    if (config->test_username == NULL) {
        fprintf(stderr, "TEST_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    config->test_password = getenv("TEST_PASSWORD");
    if (config->test_password == NULL) {
        fprintf(stderr, "TEST_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    config->test_database = getenv("TEST_DATABASE");
    if (config->test_database == NULL) {
        fprintf(stderr, "TEST_DATABASE environment variable not set\n");
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
        return 1;
    }

    printf("Test Configuration:\n");
    printf("Username: %s\n", config->test_username);
    printf("Password: %s\n", config->test_password);
    printf("Database: %s\n", config->test_database);

    destroy_test_config(config);
    return 0;
}