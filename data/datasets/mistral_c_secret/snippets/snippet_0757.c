#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_name = strdup(test_name);
    if (config->test_name == NULL) {
        free(config);
        return NULL;
    }

    const char *credential = getenv(CREDENTIAL_ENV_VAR);
    if (credential == NULL) {
        fprintf(stderr, "Credential not found in environment variables.\n");
        free(config->test_name);
        free(config);
        return NULL;
    }

    config->credential = strdup(credential);
    if (config->credential == NULL) {
        free(config->test_name);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_name);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("UnitTest");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test Configuration created successfully.\n");
    printf("Test Name: %s\n", config->test_name);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}