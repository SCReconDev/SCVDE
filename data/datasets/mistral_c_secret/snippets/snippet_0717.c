#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

typedef struct {
    char *credential;
    char *config_value;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *config_value) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->config_value = strdup(config_value);
    if (config->config_value == NULL) {
        free(config);
        return NULL;
    }

    char *credential = getenv(CREDENTIAL_ENV_VAR);
    if (credential == NULL) {
        fprintf(stderr, "Test credential not found in environment variables\n");
        free(config->config_value);
        free(config);
        return NULL;
    }

    config->credential = strdup(credential);
    if (config->credential == NULL) {
        free(config->config_value);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->credential);
        free(config->config_value);
        free(config);
    }
}

void print_test_configuration(TestConfiguration *config) {
    if (config == NULL) {
        fprintf(stderr, "Invalid test configuration\n");
        return;
    }

    printf("Test Configuration:\n");
    printf("Credential: %s\n", config->credential);
    printf("Config Value: %s\n", config->config_value);
}

int main() {
    TestConfiguration *config = create_test_configuration("test_value");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    print_test_configuration(config);
    destroy_test_configuration(config);

    return 0;
}