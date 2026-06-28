#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *service_url;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *service_url) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->service_url = strdup(service_url);
    if (config->service_url == NULL) {
        free(config);
        return NULL;
    }

    char *credential = getenv(CREDENTIAL_ENV_VAR);
    if (credential == NULL) {
        fprintf(stderr, "Credential not found in environment variables.\n");
        free(config->service_url);
        free(config);
        return NULL;
    }

    config->credential = strdup(credential);
    if (config->credential == NULL) {
        free(config->service_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->service_url);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("https://test.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    printf("Test configuration created successfully.\n");
    printf("Service URL: %s\n", config->service_url);

    destroy_test_configuration(config);
    return 0;
}