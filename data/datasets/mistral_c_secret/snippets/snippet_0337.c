#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_env;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_env) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    config->test_env = strdup(test_env);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->test_env);
    free(config->test_credential);
    free(config);
}

int main() {
    TestConfiguration *config = create_test_configuration("test_env_123");
    printf("Test Configuration created with credential: %s\n", config->test_credential);
    destroy_test_configuration(config);
    return 0;
}