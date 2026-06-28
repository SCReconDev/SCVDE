#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *test_config_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_config_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_config_name = strdup(test_config_name);
    if (config->test_config_name == NULL) {
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
    if (config->credential == NULL) {
        fprintf(stderr, "Error: Credential not found in environment variables.\n");
        free(config->test_config_name);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->test_config_name != NULL) {
            free(config->test_config_name);
        }
        if (config->credential != NULL) {
            free(config->credential);
        }
        free(config);
    }
}

int main() {
    const char *test_config_name = "test_config_1";

    TestConfiguration *config = create_test_configuration(test_config_name);

    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test Configuration created with name: %s\n", config->test_config_name);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}