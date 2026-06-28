#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *test_config;
    char *test_credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_config) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_config = strdup(test_config);
    if (config->test_config == NULL) {
        free(config);
        return NULL;
    }

    config->test_credential = strdup(TEST_CREDENTIAL);
    if (config->test_credential == NULL) {
        free(config->test_config);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_config);
        free(config->test_credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test_config_value");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test configuration created with test credential: %s\n", config->test_credential);

    destroy_test_configuration(config);
    return 0;
}