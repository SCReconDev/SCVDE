#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_config;
    char *test_credential;
} TestConfig;

TestConfig* create_test_config(const char *test_config, const char *test_credential) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }

    config->test_config = strdup(test_config);
    if (config->test_config == NULL) {
        free(config);
        return NULL;
    }

    config->test_credential = strdup(test_credential);
    if (config->test_credential == NULL) {
        free(config->test_config);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config->test_config);
        free(config->test_credential);
        free(config);
    }
}

int run_test(TestConfig *config) {
    if (config == NULL) {
        return -1;
    }

    // Simulate running a test
    printf("Running test with config: %s\n", config->test_config);
    printf("Using credential: %s\n", config->test_credential);

    return 0;
}

int main() {
    const char *test_credential = getenv("TEST_CREDENTIAL");
    if (test_credential == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set.\n");
        return 1;
    }

    TestConfig *config = create_test_config("test_config_value", test_credential);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test config.\n");
        return 1;
    }

    if (run_test(config) != 0) {
        fprintf(stderr, "Failed to run test.\n");
        destroy_test_config(config);
        return 1;
    }

    destroy_test_config(config);

    return 0;
}