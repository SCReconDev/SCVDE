#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_credential;
    char *test_endpoint;
    int test_port;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_endpoint, int test_port) {
    TestConfiguration *config = malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_endpoint = strdup(test_endpoint);
    if (config->test_endpoint == NULL) {
        free(config);
        return NULL;
    }

    config->test_port = test_port;

    config->test_credential = getenv("TEST_CREDENTIAL");
    if (config->test_credential == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set\n");
        free(config->test_endpoint);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_endpoint);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("localhost", 8080);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test configuration created for endpoint: %s\n", config->test_endpoint);
    printf("Test port: %d\n", config->test_port);

    destroy_test_configuration(config);
    return 0;
}