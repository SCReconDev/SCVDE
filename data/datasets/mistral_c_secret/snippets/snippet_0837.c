#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *database;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *username, const char *password, const char *database) {
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

    config->database = strdup(database);
    if (config->database == NULL) {
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
        free(config->database);
        free(config);
    }
}

int run_test(TestConfiguration *config) {
    if (config == NULL) {
        return -1;
    }

    printf("Running test with:\n");
    printf("Username: %s\n", config->username);
    printf("Password: %s\n", config->password);
    printf("Database: %s\n", config->database);

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

    const char *test_database = getenv("TEST_DATABASE");
    if (test_database == NULL) {
        fprintf(stderr, "TEST_DATABASE environment variable not set\n");
        return 1;
    }

    TestConfiguration *config = create_test_configuration(test_username, test_password, test_database);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    run_test(config);

    destroy_test_configuration(config);

    return 0;
}