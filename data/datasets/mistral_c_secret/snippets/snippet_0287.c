#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *environment;
    char *credential;
} TestConfig;

TestConfig* create_test_config(const char *environment) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    config->environment = strdup(environment);
    config->credential = strdup(TEST_CREDENTIAL);
    return config;
}

void run_test(TestConfig *config) {
    printf("Running test in environment: %s with credential: %s\n", config->environment, config->credential);
}

void destroy_test_config(TestConfig *config) {
    free(config->environment);
    free(config->credential);
    free(config);
}

int main() {
    TestConfig *config = create_test_config("test");
    run_test(config);
    destroy_test_config(config);
    return 0;
}