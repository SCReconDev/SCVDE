#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_VALUE_ENV_VAR "TEST_CONFIG_VALUE"

typedef struct {
    char* value;
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration* config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->value = getenv(TEST_CONFIG_VALUE_ENV_VAR);
    if (config->value == NULL) {
        fprintf(stderr, "Error: Test configuration value not found in environment variables.\n");
        free(config);
        return NULL;
    }
    return config;
}

void destroy_test_configuration(TestConfiguration* config) {
    if (config != NULL) {
        free(config);
    }
}

void print_test_configuration(TestConfiguration* config) {
    if (config != NULL && config->value != NULL) {
        printf("Test configuration value: %s\n", config->value);
    }
}

int main() {
    TestConfiguration* config = create_test_configuration();
    if (config == NULL) {
        return 1;
    }
    print_test_configuration(config);
    destroy_test_configuration(config);
    return 0;
}