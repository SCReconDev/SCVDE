#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL "fake_credential_1234567890"

typedef struct {
    char *test_config_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_config_name = strdup(name);
    config->credential = strdup(CREDENTIAL);

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_config_name);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("TestConfig1");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created with name: %s\n", config->test_config_name);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}