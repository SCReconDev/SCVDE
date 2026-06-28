#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *environment;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *environment) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->environment = strdup(environment);
    config->credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->environment);
    free(config->credential);
    free(config);
}

void run_test(TestConfiguration *config) {
    printf("Running test in environment %s with credential %s\n", config->environment, config->credential);
}

int main() {
    TestConfiguration *config = create_test_configuration("test");
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}