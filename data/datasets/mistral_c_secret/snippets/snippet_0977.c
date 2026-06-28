#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

typedef struct {
    char *test_server;
    int test_port;
    char *test_credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_server, int test_port) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_server = strdup(test_server);
    config->test_port = test_port;

    if (config->test_server == NULL) {
        free(config);
        return NULL;
    }

    const char *credential = getenv(CREDENTIAL_ENV_VAR);
    if (credential == NULL) {
        fprintf(stderr, "Error: Test credential not found in environment variables.\n");
        free(config->test_server);
        free(config);
        return NULL;
    }

    config->test_credential = strdup(credential);
    if (config->test_credential == NULL) {
        free(config->test_server);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_server);
        free(config->test_credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test.example.com", 8080);
    if (config == NULL) {
        return EXIT_FAILURE;
    }

    printf("Test configuration created.\n");
    printf("Test Server: %s\n", config->test_server);
    printf("Test Port: %d\n", config->test_port);

    destroy_test_configuration(config);
    return EXIT_SUCCESS;
}