#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_URL "https://test.example.com"
#define CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

typedef struct {
    char *url;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *url) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->url = strdup(url);
    if (config->url == NULL) {
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
    if (config->credential == NULL) {
        fprintf(stderr, "Test credential not found in environment variables.\n");
        free(config->url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->url != NULL) {
            free(config->url);
        }
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration(TEST_CONFIG_URL);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test Configuration created successfully.\n");
    printf("URL: %s\n", config->url);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}