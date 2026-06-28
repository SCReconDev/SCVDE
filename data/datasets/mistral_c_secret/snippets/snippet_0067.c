#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *config_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *config_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    config->config_name = strdup(config_name);
    config->credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->config_name);
    free(config->credential);
    free(config);
}

void run_test(TestConfiguration *config) {
    printf("Running test with configuration: %s and credential: %s\n", config->config_name, config->credential);
}

int main() {
    TestConfiguration *config = create_test_configuration("test_config");
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}