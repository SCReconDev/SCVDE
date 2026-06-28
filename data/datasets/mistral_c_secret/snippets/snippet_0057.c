#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_url;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_url) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->test_url = strdup(test_url);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_url);
        free(config->test_credential);
        free(config);
    }
}

int run_test(TestConfiguration *config) {
    if (config == NULL) {
        return -1;
    }
    printf("Running test on %s with credential %s\n", config->test_url, config->test_credential);
    return 0;
}

int main() {
    TestConfiguration *config = create_test_configuration("https://test.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}