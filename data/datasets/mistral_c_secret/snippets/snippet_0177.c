#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL "fake_credential_1234567890"

typedef struct {
    char *service_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *service_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->service_name = strdup(service_name);
    config->credential = strdup(CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->service_name);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test_service");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}