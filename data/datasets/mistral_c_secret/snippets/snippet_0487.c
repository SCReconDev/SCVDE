#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *config_name;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *config_name) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->config_name = strdup(config_name);
    config->credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->config_name);
        free(config->credential);
        free(config);
    }
}

int run_test(TestConfiguration *config) {
    printf("Running test %s with credential %s\n", config->config_name, config->credential);
    return 0;
}

int main() {
    TestConfiguration *config = create_test_configuration("Test Config");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}