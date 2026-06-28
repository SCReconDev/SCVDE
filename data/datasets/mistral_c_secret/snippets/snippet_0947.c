#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *service_url;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *service_url) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->service_url = strdup(service_url);
    if (config->service_url == NULL) {
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
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
        free(config);
    }
}

int main() {
    const char *service_url = "https://test.example.com";

    TestConfiguration *config = create_test_configuration(service_url);

    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with URL: %s\n", config->service_url);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}