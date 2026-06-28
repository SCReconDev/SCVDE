#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_URL "https://test.example.com/v1"
#define TEST_CREDENTIAL_ENV "TEST_CREDENTIAL"

typedef struct {
    char *url;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration() {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->url = strdup(TEST_CONFIG_URL);
    if (config->url == NULL) {
        free(config);
        return NULL;
    }

    char *credential = getenv(TEST_CREDENTIAL_ENV);
    if (credential == NULL) {
        free(config->url);
        free(config);
        return NULL;
    }

    config->credential = strdup(credential);
    if (config->credential == NULL) {
        free(config->url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->url);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration();
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with URL: %s and Credential: %s\n", config->url, config->credential);

    destroy_test_configuration(config);
    return 0;
}