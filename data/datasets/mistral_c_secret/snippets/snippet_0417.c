#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL "fake_credential_1234567890"

typedef struct {
    char *test_config;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_config) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->test_config = strdup(test_config);
    config->credential = strdup(CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_config);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test_config_123");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}