#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_FILE "test_config.json"
#define CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

typedef struct {
    char *file;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *file) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->file = strdup(file);
    if (config->file == NULL) {
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
    if (config->credential == NULL) {
        fprintf(stderr, "Error: Test credential not found in environment variables.\n");
        free(config->file);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->file != NULL) {
            free(config->file);
        }
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration(TEST_CONFIG_FILE);
    if (config == NULL) {
        return 1;
    }

    printf("Test configuration created successfully.\n");
    printf("File: %s\n", config->file);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}