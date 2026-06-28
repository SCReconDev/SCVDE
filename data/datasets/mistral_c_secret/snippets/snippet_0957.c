#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *config_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *config_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->config_name = strdup(config_name);
    if (config->config_name == NULL) {
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
    if (config->credential == NULL) {
        fprintf(stderr, "Credential not found in environment variables.\n");
        free(config->config_name);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->config_name);
        free(config);
    }
}

int main() {
    const char *config_name = "test_config";
    TestConfiguration *config = create_test_configuration(config_name);

    if (config != NULL) {
        printf("Test Configuration created successfully.\n");
        destroy_test_configuration(config);
    } else {
        printf("Failed to create Test Configuration.\n");
    }

    return 0;
}