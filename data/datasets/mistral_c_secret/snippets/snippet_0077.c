#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_server;
    int test_port;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_server, int test_port) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_server = strdup(test_server);
    config->test_port = test_port;
    config->test_credential = strdup(TEST_CREDENTIAL);

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_server);
        free(config->test_credential);
        free(config);
    }
}

int run_test(TestConfiguration *config) {
    if (config == NULL) {
        return -1;
    }

    printf("Running test on server %s:%d with credential %s\n", config->test_server, config->test_port, config->test_credential);
    return 0;
}

int main() {
    TestConfiguration *config = create_test_configuration("test.example.com", 8080);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    run_test(config);

    destroy_test_configuration(config);
    return 0;
}