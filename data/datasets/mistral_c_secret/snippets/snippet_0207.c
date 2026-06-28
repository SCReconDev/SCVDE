#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL "fake_credential_uvwxy"

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_name) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_name = strdup(test_name);
    config->credential = strdup(CREDENTIAL);

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_name);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("unit_test_1");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created for test: %s\n", config->test_name);
    destroy_test_configuration(config);

    return 0;
}