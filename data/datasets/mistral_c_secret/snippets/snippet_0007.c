#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_env;
    char *test_credential;
} TestConfig;

TestConfig *create_test_config(const char *test_env) {
    TestConfig *config = (TestConfig *)malloc(sizeof(TestConfig));
    config->test_env = strdup(test_env);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_config(TestConfig *config) {
    free(config->test_env);
    free(config->test_credential);
    free(config);
}

int main() {
    TestConfig *config = create_test_config("test_env_123");
    printf("Test config created with credential: %s\n", config->test_credential);
    destroy_test_config(config);
    return 0;
}