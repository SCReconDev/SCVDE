#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_DB_HOST_ENV_VAR "TEST_DB_HOST"
#define TEST_DB_USER_ENV_VAR "TEST_DB_USER"
#define TEST_DB_PASSWORD_ENV_VAR "TEST_DB_PASSWORD"
#define TEST_DB_NAME_ENV_VAR "TEST_DB_NAME"

typedef struct {
    char *host;
    char *user;
    char *password;
    char *name;
} TestConfiguration;

TestConfiguration *create_test_configuration() {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    char *host = getenv(TEST_DB_HOST_ENV_VAR);
    char *user = getenv(TEST_DB_USER_ENV_VAR);
    char *password = getenv(TEST_DB_PASSWORD_ENV_VAR);
    char *name = getenv(TEST_DB_NAME_ENV_VAR);

    if (host == NULL || user == NULL || password == NULL || name == NULL) {
        fprintf(stderr, "Error: Test database credentials not found in environment variables.\n");
        free(config);
        return NULL;
    }

    config->host = strdup(host);
    config->user = strdup(user);
    config->password = strdup(password);
    config->name = strdup(name);

    if (config->host == NULL || config->user == NULL ||
        config->password == NULL || config->name == NULL) {
        free(config->host);
        free(config->user);
        free(config->password);
        free(config->name);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->host);
        free(config->user);
        free(config->password);
        free(config->name);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration();
    if (config == NULL) {
        return 1;
    }

    printf("Test Configuration created successfully.\n");
    printf("Host: %s\n", config->host);
    printf("User: %s\n", config->user);
    printf("Password: %s\n", config->password);
    printf("Name: %s\n", config->name);

    destroy_test_configuration(config);
    return 0;
}