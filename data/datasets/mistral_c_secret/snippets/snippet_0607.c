#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *config_name;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *config_name) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
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
    TestConfiguration *config = create_test_configuration("test_config");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test configuration created with credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}