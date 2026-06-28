#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_ENV_VAR "TEST_CONFIG"

typedef struct {
    char *config;
} TestConfig;

TestConfig* create_config() {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    config->config = getenv(TEST_CONFIG_ENV_VAR);
    if (config->config == NULL) {
        fprintf(stderr, "Error: Test configuration not found in environment variables.\n");
        free(config);
        return NULL;
    }
    return config;
}

void destroy_config(TestConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int run_test(TestConfig *config) {
    if (config == NULL || config->config == NULL) {
        return -1;
    }
    printf("Running test with configuration: %s\n", config->config);
    return 0;
}

int main() {
    TestConfig *config = create_config();
    if (config == NULL) {
        return EXIT_FAILURE;
    }
    run_test(config);
    destroy_config(config);
    return EXIT_SUCCESS;
}