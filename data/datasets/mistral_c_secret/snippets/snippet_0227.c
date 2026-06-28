#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_name;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->test_name = strdup(test_name);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_name);
        free(config->test_credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test_123");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return EXIT_FAILURE;
    }

    printf("Test Configuration created with credential: %s\n", config->test_credential);

    destroy_test_configuration(config);
    return EXIT_SUCCESS;
}